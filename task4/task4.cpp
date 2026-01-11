#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "task4.hpp"

namespace {

void generateSubsets(const std::vector<std::string>& items, size_t index,
                     std::vector<std::string>& current,
                     std::vector<std::vector<std::string>>& out) {
    if (index == items.size()) {
        out.push_back(current);
        return;
    }

    generateSubsets(items, index + 1, current, out);
    current.push_back(items[index]);
    generateSubsets(items, index + 1, current, out);
    current.pop_back();
}

void printSubsets(const std::vector<std::vector<std::string>>& subsets) {
    std::cout << "Результат работы алгоритма: [";
    for (size_t i = 0; i < subsets.size(); ++i) {
        const auto& subset = subsets[i];
        std::cout << "{";
        for (size_t j = 0; j < subset.size(); ++j) {
            std::cout << subset[j];
            if (j + 1 < subset.size()) std::cout << ", ";
        }
        std::cout << "}";
        if (i + 1 < subsets.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

}  // namespace

void runTask4() {
    std::cout << "Размер массива: ";
    int n = 0;
    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Нужно неотрицательное число.\n";
        return;
    }

    std::vector<std::string> items(static_cast<size_t>(n));
    std::cout << "Введите элементы массива:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> items[i];
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::string> current;
    std::vector<std::vector<std::string>> subsets;
    generateSubsets(items, 0, current, subsets);
    printSubsets(subsets);
}
