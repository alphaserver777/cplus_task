#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

#include "tasks.hpp"

namespace {

bool backtrack(const std::vector<int>& nums, std::vector<int>& bucketSum,
               std::vector<std::vector<int>>& buckets, int target, size_t idx) {
    if (idx == nums.size()) return true;
    int value = nums[idx];

    for (size_t i = 0; i < buckets.size(); ++i) {
        if (bucketSum[i] + value <= target) {
            bucketSum[i] += value;
            buckets[i].push_back(value);
            if (backtrack(nums, bucketSum, buckets, target, idx + 1)) return true;
            bucketSum[i] -= value;
            buckets[i].pop_back();
        }
        if (bucketSum[i] == 0) break;  // симметрия, чтобы не повторять пустые корзины
    }
    return false;
}

bool splitIntoEqualSums(const std::vector<int>& input, int target,
                        std::vector<std::vector<int>>& result) {
    long long total = std::accumulate(input.begin(), input.end(), 0LL);
    if (target <= 0 || total % target != 0) return false;

    size_t groups = static_cast<size_t>(total / target);
    if (groups == 0) return false;

    std::vector<int> nums = input;
    std::sort(nums.rbegin(), nums.rend());  // крупные числа сначала

    std::vector<int> bucketSum(groups, 0);
    result.assign(groups, {});
    return backtrack(nums, bucketSum, result, target, 0);
}

}  // namespace

void runPartitionDemo() {
    std::cout << "Целевая сумма подмножества: ";
    int target = 0;
    if (!(std::cin >> target)) {
        std::cerr << "Не удалось прочитать число.\n";
        return;
    }

    std::cout << "Введите элементы множества (натуральные числа), завершите символом 0:\n";
    std::vector<int> nums;
    int value = 0;
    while (std::cin >> value && value != 0) {
        nums.push_back(value);
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::vector<int>> parts;
    if (splitIntoEqualSums(nums, target, parts)) {
        std::cout << "Множество разбито на " << parts.size() << " подмножеств:\n";
        for (const auto& group : parts) {
            std::cout << "{ ";
            for (int x : group) std::cout << x << ' ';
            std::cout << "}\n";
        }
    } else {
        std::cout << "Разбиение невозможно.\n";
    }
}
