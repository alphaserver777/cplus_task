#include <iostream>
#include <limits>
#include <unordered_map>
#include <utility>
#include <vector>

#include "task4.hpp"

namespace {

std::vector<std::pair<int, int>> findSubarraysWithSum(const std::vector<int>& nums, int k) {
    std::unordered_map<long long, std::vector<int>> prefixIndices;
    std::vector<std::pair<int, int>> result;

    long long prefix = 0;
    prefixIndices[0].push_back(-1);

    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        prefix += nums[i];
        long long need = prefix - k;
        auto it = prefixIndices.find(need);
        if (it != prefixIndices.end()) {
            for (int startIdx : it->second) {
                result.emplace_back(startIdx + 1, i);
            }
        }
        prefixIndices[prefix].push_back(i);
    }
    return result;
}

void printSubarray(const std::vector<int>& nums, int l, int r) {
    std::cout << "[ ";
    for (int i = l; i <= r; ++i) {
        std::cout << nums[i] << ' ';
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

    std::vector<int> nums(static_cast<size_t>(n));
    std::cout << "Введите элементы массива:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> nums[i];
    }

    std::cout << "Введите K: ";
    int k = 0;
    if (!(std::cin >> k)) {
        std::cerr << "Не удалось прочитать K.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto subarrays = findSubarraysWithSum(nums, k);
    if (subarrays.empty()) {
        std::cout << "Подмассивы с суммой K не найдены.\n";
        return;
    }

    std::cout << "Найдены подмассивы:\n";
    for (const auto& [l, r] : subarrays) {
        printSubarray(nums, l, r);
    }
}
