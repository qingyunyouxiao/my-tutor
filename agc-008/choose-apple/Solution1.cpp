#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>

struct Apple {
    std::string color;
    int weight;
};

int main() {
    std::vector<Apple> inventory = {
        {"red", 160}, {"green", 120}, {"red", 140}, {"red", 180}
    };

    // copy_if(source_begin, source_end, destination_position, lambda condition);
    std::vector<Apple> redAndHeavyApples;
    std::copy_if(inventory.begin(), inventory.end(), 
                 std::back_inserter(redAndHeavyApples),
                 [](const Apple& apple) {
                     return apple.color == "red" && apple.weight > 150;
                 });

    for (const auto& apple : redAndHeavyApples) {
        std::cout << apple.color << ": " << apple.weight << "\n";
    }
}