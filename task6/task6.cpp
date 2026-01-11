#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <random>
#include <string>
#include <vector>

#include "task6.hpp"

namespace {

class HashTableChaining {
public:
    explicit HashTableChaining(size_t buckets) : buckets_(buckets) {
        if (buckets_ == 0) buckets_ = 1;
        table_.resize(buckets_);
    }

    void insert(int key) {
        auto& bucket = table_[hash(key)];
        if (std::find(bucket.begin(), bucket.end(), key) == bucket.end()) {
            bucket.push_back(key);
        }
    }

    bool contains(int key) const {
        const auto& bucket = table_[hash(key)];
        return std::find(bucket.begin(), bucket.end(), key) != bucket.end();
    }

private:
    size_t hash(int key) const { return (static_cast<size_t>(key) % buckets_ + buckets_) % buckets_; }

    size_t buckets_;
    std::vector<std::vector<int>> table_;
};

class HashTableOpenAddressing {
public:
    explicit HashTableOpenAddressing(size_t capacity) : capacity_(capacity) {
        if (capacity_ == 0) capacity_ = 1;
        keys_.assign(capacity_, std::nullopt);
        used_.assign(capacity_, false);
    }

    void insert(int key) {
        size_t idx = findSlot(key);
        if (!used_[idx]) {
            keys_[idx] = key;
            used_[idx] = true;
        } else if (!keys_[idx].has_value()) {
            keys_[idx] = key;
        } else if (keys_[idx].value() == key) {
            return;
        }
    }

    bool contains(int key) const {
        size_t idx = hash1(key);
        size_t step = hash2(key);
        for (size_t i = 0; i < capacity_; ++i) {
            size_t probe = (idx + i * step) % capacity_;
            if (!used_[probe]) return false;
            if (keys_[probe].has_value() && keys_[probe].value() == key) return true;
        }
        return false;
    }

private:
    size_t findSlot(int key) const {
        size_t idx = hash1(key);
        size_t step = hash2(key);
        for (size_t i = 0; i < capacity_; ++i) {
            size_t probe = (idx + i * step) % capacity_;
            if (!used_[probe] || !keys_[probe].has_value() || keys_[probe].value() == key) {
                return probe;
            }
        }
        return 0;
    }

    size_t hash1(int key) const {
        return (static_cast<size_t>(key) % capacity_ + capacity_) % capacity_;
    }

    size_t hash2(int key) const {
        // вторичная функция — простое смещение
        return 1 + (static_cast<size_t>(key) % (capacity_ - 1));
    }

    size_t capacity_;
    std::vector<std::optional<int>> keys_;
    std::vector<bool> used_;
};

template <class Table>
long long measureContains(Table& table, const std::vector<int>& queries) {
    auto start = std::chrono::high_resolution_clock::now();
    size_t found = 0;
    for (int q : queries) {
        if (table.contains(q)) ++found;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> diff = end - start;
    std::cout << "Найдено совпадений: " << found << "\n";
    return static_cast<long long>(diff.count());
}

std::vector<int> buildData(size_t n) {
    std::vector<int> data(n);
    for (size_t i = 0; i < n; ++i) data[i] = static_cast<int>(i * 7 + 3);
    return data;
}

std::vector<int> buildQueries(size_t m, size_t n) {
    std::vector<int> q(m);
    for (size_t i = 0; i < m; ++i) {
        q[i] = static_cast<int>((i * 13) % (n * 2));
    }
    return q;
}

}  // namespace

void runTask6() {
    size_t n = 0;
    size_t m = 0;
    std::cout << "Количество элементов для вставки: ";
    if (!(std::cin >> n) || n == 0) {
        std::cerr << "Нужно положительное число элементов.\n";
        return;
    }
    std::cout << "Количество поисков: ";
    if (!(std::cin >> m) || m == 0) {
        std::cerr << "Нужно положительное число поисков.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto data = buildData(n);
    auto queries = buildQueries(m, n);

    HashTableChaining chaining(n / 2 + 1);
    HashTableOpenAddressing open(n * 2 + 1);

    for (int x : data) {
        chaining.insert(x);
        open.insert(x);
    }

    std::cout << "=== Метод цепочек ===\n";
    long long timeChains = measureContains(chaining, queries);
    std::cout << "Время: " << timeChains << " микросекунд\n\n";

    std::cout << "=== Открытая адресация (двойное хеширование) ===\n";
    long long timeOpen = measureContains(open, queries);
    std::cout << "Время: " << timeOpen << " микросекунд\n";
}
