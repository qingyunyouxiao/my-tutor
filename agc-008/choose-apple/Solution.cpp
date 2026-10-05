#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <algorithm>

// First, define the Apple struct
struct Apple {
    std::string color;
    int weight;
};

// Define the inventory
int main() {
    std::vector<Apple> inventory = {
        {"red", 160}, {"green", 120}, {"red", 140}, {"red", 180}
    };

    // Loop
    for (const auto& apple : inventory) {
        if (apple.color == "red" && apple.weight > 150) {
            std::cout << apple.color << ": " << apple.weight << "\n";
        }
    }

    return 0;
}