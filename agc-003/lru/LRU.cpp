#include <chrono>
#include <concepts>
#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
#include <optional>
#include <unordered_map>
#include <utility>

template <typename K, typename V>
    requires std::copyable<K> && std::copyable<V>
class LRUCache {
public:

    using Entry = std::pair<K, V>;
    using List  = std::list<Entry>;
    using Iter  = typename List::iterator;
 
    // 类给成员变量赋值的方法
    explicit LRUCache(int capacity) : capacity_(capacity) {}

    // 命中返回 value，未命中返回 std::nullopt
    std::optional<V> get(const K& key) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = index_.find(key);
        if (it == index_.end()) return std::nullopt;

        order_.splice(order_.begin(), order_, it->second); // 提到最前
        return it->second->second;
    }

    void put(K key, V value) {
        std::lock_guard<std::mutex> lock(mtx_);
        auto it = index_.find(key);
        if (it != index_.end()) {
            it->second->second = std::move(value);
            order_.splice(order_.begin(), order_, it->second);
            return;
        }
        if (order_.size() >= capacity_) {
            const auto& old = order_.back().first;
            index_.erase(old);
            order_.pop_back();
        }
        order_.emplace_front(std::move(key), std::move(value));
        index_[order_.begin()->first] = order_.begin();
    }

    // 阻塞式取：key 不存在时等待，适合“生产者写入、消费者读取”场景
    V wait_and_get(const K& key,
                   std::chrono::milliseconds timeout = std::chrono::seconds(5)) {
        std::unique_lock<std::mutex> lock(mtx_);
        if (!cv_.wait_for(lock, timeout,
                          [&] { return index_.contains(key); })) {
            throw std::runtime_error("wait_and_get timeout");
        }
        auto it = index_.find(key);
        order_.splice(order_.begin(), order_, it->second);
        return it->second->second;
    }

    void notify_put(const K& key) {   // 写入后唤醒等待者
        std::lock_guard<std::mutex> lock(mtx_);
        if (index_.contains(key)) cv_.notify_all();
    }

    std::size_t size()  const { std::lock_guard<std::mutex> l(mtx_); return order_.size(); }
    std::size_t capacity() const { return capacity_; }

private:
    std::size_t       capacity_;
    List              order_;                         // 最近使用 → 最久未用
    std::unordered_map<K, Iter> index_;
    mutable std::mutex          mtx_;
    std::condition_variable     cv_;
};

int main() {
    // 创建一个LRUCache，键为 int，值为 string，允许插入的键值容量为3
    LRUCache<int, std::string> cache(3);

    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    if (auto v = cache.get(1)) std::cout << "get(1) = " << *v << '\n';   // one
    if (auto v = cache.get(4)) std::cout << "get(4) = " << *v << '\n';   // 不输出

    cache.put(4, "four");   // 淘汰 key=2
    if (auto v = cache.get(2)) std::cout << "get(2) = " << *v << '\n';   // 不输出
    if (auto v = cache.get(4)) std::cout << "get(4) = " << *v << '\n';   // four

    std::cout << "size = " << cache.size() << " / " << cache.capacity() << '\n';
}