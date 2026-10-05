#include <atomic>
#include <iostream>

class AtomicSpinCounter {
private:
    // 对应 Java 中的 AtomicInteger，初始化为 0
    std::atomic<int> atomicVar{0};

public:
    void doSomething() {
        // 对应 int localVar = atomicVar.get();
        int localVar = atomicVar.load();

        // 对应 while (!atomicVar.compareAndSet(localVar, localVar + 1))
        // compare_exchange_weak 是 C++ 中常用的 CAS 操作，在自旋循环中性能通常更好
        while (!atomicVar.compare_exchange_weak(localVar, localVar + 1)) {
            // 如果 CAS 失败，compare_exchange_weak 会自动将 localVar 更新为当前的最新值
            // 所以这里不需要像 Java 那样显式地重新调用 get()
        }

        std::cout << "hello" << std::endl;
    }
};

int main() {
    AtomicSpinCounter h;
    h.doSomething();
    return 0;
}

// 声明（Declaration）：定义变量、方法、类型等，可以放在类体/模块顶层
// 可执行语句（Statement）：赋值、函数调用、循环、条件判断等，必须放在方法或初始化块内部

// import java.util.concurrent.atomic.AtomicInteger;

// public class Hello {
//     private final AtomicInteger atomicVar = new AtomicInteger(0);

//     public void doSomething() {
//         int localVar = atomicVar.get();
//         while (!atomicVar.compareAndSet(localVar, localVar + 1)) {
//             localVar = atomicVar.get();
//         }
//         System.out.println("hello");
//     }
// }