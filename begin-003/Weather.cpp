#include <algorithm>
#include <concepts>
#include <iostream>
#include <memory>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>
#include <format>

enum class WeatherType {
    SUNNY,
    RAINY,
    WINDY,
    COLD
};

// C++20: 返回 string_view，避免不必要的字符串拷贝
constexpr std::string_view getDescription(WeatherType type) noexcept {
    switch (type) {
        case WeatherType::SUNNY: return "Sunny";
        case WeatherType::RAINY: return "Rainy";
        case WeatherType::WINDY: return "Windy";
        case WeatherType::COLD:  return "Cold";
    }
    return "Unknown";
}

class WeatherObserver {
public:
    virtual ~WeatherObserver() = default;
    virtual void update(WeatherType currentWeather) = 0;
};

// C++20 concept：约束可被注册的观察者类型
template <typename T>
concept Observable = std::derived_from<T, WeatherObserver>;

class Orcs : public WeatherObserver {
public:
    void update(WeatherType currentWeather) override {
        std::cout << std::format("The orcs are facing {} weather now\n",
                                getDescription(currentWeather));
    }
};

class Hobbits : public WeatherObserver {
public:
    void update(WeatherType currentWeather) override {
        switch (currentWeather) {
            case WeatherType::SUNNY:
                std::cout << "The hobbits are enjoying the sunshine.\n";
                break;
            case WeatherType::RAINY:
                std::cout << "The hobbits are staying indoors due to rain.\n";
                break;
            default:
                std::cout << std::format("The hobbits are facing {} weather now\n",
                                        getDescription(currentWeather));
                break;
        }
    }
};

class WeatherStation {
public:
    // C++20 concept 约束，编译期就能拦截错误类型
    template <Observable T>
    void addObserver(std::shared_ptr<T> observer) {
        if (observer) {
            observers_.push_back(std::move(observer));
        }
    }

    void removeObserver(const std::shared_ptr<WeatherObserver>& observer) {
        std::erase_if(observers_, [&observer](const std::weak_ptr<WeatherObserver>& w) {
            auto sp = w.lock();
            return !sp || sp == observer;
        });
    }

    void setWeather(WeatherType weather) {
        currentWeather_ = weather;
        std::cout << std::format("Weather changed to: {}\n", getDescription(weather));
        notifyObservers();
    }

private:
    void notifyObservers() {
        // C++20: std::erase_if 替代 erase-remove 惯用法
        std::erase_if(observers_,
                      [](const std::weak_ptr<WeatherObserver>& w) { return w.expired(); });

        for (const auto& weak : observers_) {
            if (auto sp = weak.lock()) {
                sp->update(currentWeather_);
            }
        }
    }

    std::vector<std::weak_ptr<WeatherObserver>> observers_;
    WeatherType currentWeather_{WeatherType::SUNNY};
};

int main() {
    WeatherStation station;

    auto orcs = std::make_shared<Orcs>();
    {
        auto hobbits = std::make_shared<Hobbits>();
        station.addObserver(orcs);
        station.addObserver(hobbits);

        std::cout << "--- Test 1: Sunny ---\n";
        station.setWeather(WeatherType::SUNNY);
    }

    std::cout << "\n--- Test 2: Rainy (hobbits already destroyed) ---\n";
    station.setWeather(WeatherType::RAINY);

    return 0;
}