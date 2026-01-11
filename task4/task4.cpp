#include <iostream>
#include <limits>
#include <vector>

#include "task4.hpp"

namespace {

void generateSubsets(const std::vector<int>& nums, size_t index, std::vector<int>& current) {
    if (index == nums.size()) {
        std::cout << "{ ";
        for (int v : current) {
            std::cout << v << ' ';
        }
        std::cout << "}\n";
        return;
    }

    generateSubsets(nums, index + 1, current);
    current.push_back(nums[index]);
    generateSubsets(nums, index + 1, current);
    current.pop_back();
}

}  // namespace

void runTask4() {
    std::cout << "Размер массива: ";
    int n = 0;
    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Нужно неотрицательное число.\n";
        return;
    }

    std::vector<int> nums(static_cast<size_t>(n));
    std::cout << "Введите элементы массива:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<int> current;
    std::cout << "Все подмножества:\n";
    generateSubsets(nums, 0, current);
}
