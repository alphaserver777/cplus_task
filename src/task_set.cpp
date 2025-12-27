#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>

#include "tasks.hpp"

namespace {

void loadData(const std::string& path, std::unordered_set<int>& data) {
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

void runSetOperations() {
    std::unordered_set<int> data;
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
            std::cout << (data.count(value) ? "YES\n" : "NO\n");
        } else {
            std::cout << "Неизвестная команда.\n";
        }
    }
}
