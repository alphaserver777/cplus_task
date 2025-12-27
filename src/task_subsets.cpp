#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "tasks.hpp"

namespace {

void generateSubsets(const std::vector<std::string>& items, size_t index,
                     std::vector<std::string>& current) {
    if (index == items.size()) {
        std::cout << "{ ";
        for (const auto& v : current) std::cout << v << ' ';
        std::cout << "}\n";
        return;
    }
    // Без текущего элемента
    generateSubsets(items, index + 1, current);
    // С текущим элементом
    current.push_back(items[index]);
    generateSubsets(items, index + 1, current);
    current.pop_back();
}

}  // namespace

void runSubsetsDemo() {
    std::cout << "Количество элементов массива: ";
    int n = 0;
    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Нужно неотрицательное число.\n";
        return;
    }

    std::vector<std::string> items(static_cast<size_t>(n));
    std::cout << "Введите элементы через пробел:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> items[i];
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::string> current;
    std::cout << "Все подмножества:\n";
    generateSubsets(items, 0, current);
}
