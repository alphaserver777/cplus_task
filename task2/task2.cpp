#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "task2.hpp"

namespace {

class HashTableSet {
public:
    HashTableSet() { rehash(16); }

    void insert(int key) {
        if (contains(key)) return;
        if (static_cast<double>(size_ + 1) / capacity_ > 0.7) {
            rehash(capacity_ * 2);
        }
        size_t idx = findSlot(key);
        keys_[idx] = key;
        state_[idx] = State::Occupied;
        ++size_;
    }

    void erase(int key) {
        size_t idx = hash(key);
        for (size_t i = 0; i < capacity_; ++i) {
            size_t probe = (idx + i) % capacity_;
            if (state_[probe] == State::Empty) return;
            if (state_[probe] == State::Occupied && keys_[probe] == key) {
                state_[probe] = State::Deleted;
                --size_;
                return;
            }
        }
    }

    bool contains(int key) const {
        size_t idx = hash(key);
        for (size_t i = 0; i < capacity_; ++i) {
            size_t probe = (idx + i) % capacity_;
            if (state_[probe] == State::Empty) return false;
            if (state_[probe] == State::Occupied && keys_[probe] == key) return true;
        }
        return false;
    }

    size_t size() const { return size_; }

private:
    enum class State { Empty, Occupied, Deleted };

    size_t hash(int key) const {
        long long mod = static_cast<long long>(key) % static_cast<long long>(capacity_);
        if (mod < 0) mod += static_cast<long long>(capacity_);
        return static_cast<size_t>(mod);
    }

    size_t findSlot(int key) const {
        size_t idx = hash(key);
        size_t firstDeleted = capacity_;
        for (size_t i = 0; i < capacity_; ++i) {
            size_t probe = (idx + i) % capacity_;
            if (state_[probe] == State::Occupied && keys_[probe] == key) return probe;
            if (state_[probe] == State::Deleted && firstDeleted == capacity_) {
                firstDeleted = probe;
            }
            if (state_[probe] == State::Empty) {
                return (firstDeleted != capacity_) ? firstDeleted : probe;
            }
        }
        return (firstDeleted != capacity_) ? firstDeleted : 0;
    }

    void rehash(size_t newCapacity) {
        std::vector<int> oldKeys;
        oldKeys.reserve(size_);
        for (size_t i = 0; i < capacity_; ++i) {
            if (i < state_.size() && state_[i] == State::Occupied) {
                oldKeys.push_back(keys_[i]);
            }
        }

        capacity_ = newCapacity;
        keys_.assign(capacity_, 0);
        state_.assign(capacity_, State::Empty);
        size_ = 0;

        for (int k : oldKeys) insert(k);
    }

    size_t capacity_ = 0;
    size_t size_ = 0;
    std::vector<int> keys_;
    std::vector<State> state_;
};

void loadData(const std::string& path, HashTableSet& data) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << "Не удалось открыть файл: " << path << "\n";
        return;
    }
    int value = 0;
    while (in >> value) {
        data.insert(value);
    }
}

void printHelp() {
    std::cout << "Команды:\n"
              << "  SETADD <x>  — добавить число\n"
              << "  SETDEL <x>  — удалить число\n"
              << "  SET_AT <x>  — проверить наличие\n"
              << "  EXIT        — выход в главное меню\n";
}

}  // namespace

void runTask2() {
    HashTableSet data;
    std::cout << "Путь к файлу с данными (по умолчанию data/set_data.txt): ";
    std::string path;
    std::getline(std::cin, path);
    if (path.empty()) path = "data/set_data.txt";
    loadData(path, data);

    std::cout << "Загружено " << data.size() << " элементов.\n";
    printHelp();

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string cmd;
        int value = 0;
        ss >> cmd;
        if (cmd == "EXIT") break;
        if (!(ss >> value)) {
            std::cout << "Укажите число после команды.\n";
            continue;
        }

        if (cmd == "SETADD") {
            data.insert(value);
            std::cout << "Добавлено.\n";
        } else if (cmd == "SETDEL") {
            data.erase(value);
            std::cout << "Удалено (если было).\n";
        } else if (cmd == "SET_AT") {
            std::cout << (data.contains(value) ? "YES\n" : "NO\n");
        } else {
            std::cout << "Неизвестная команда.\n";
        }
    }
}
