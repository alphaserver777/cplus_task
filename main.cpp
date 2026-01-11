#include <iostream>
#include <limits>
#include "task1/task1.hpp"
#include "task2/task2.hpp"
#include "task3/task3.hpp"
#include "task4/task4.hpp"
#include "task5/task5.hpp"
#include "task6/task6.hpp"
#include "task7/task7.hpp"

int main() {
    std::cout << "Учебный проект (C++) — выберите задание:\n";
    std::cout << "1. Вычисление арифметического выражения\n";
    std::cout << "2. Операции со множеством из файла\n";
    std::cout << "3. Разбиение множества на равные суммы\n";
    std::cout << "4. Все непрерывные подмассивы с суммой K\n";
    std::cout << "5. Проверка АВЛ-сбалансированности дерева поиска\n";
    std::cout << "6. Хеш-таблица: цепочки vs открытая адресация\n";
    std::cout << "7. Родословная: число потомков\n";
    std::cout << "0. Выход\n\n";

    int choice = -1;
    std::cout << "Введите номер задания: ";
    if (!(std::cin >> choice)) {
        std::cerr << "Не удалось прочитать номер задания.\n";
        return 1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case 1:
            runTask1();
            break;
        case 2:
            runTask2();
            break;
        case 3:
            runTask3();
            break;
        case 4:
            runTask4();
            break;
        case 5:
            runTask5();
            break;
        case 6:
            runTask6();
            break;
        case 7:
            runTask7();
            break;
        case 0:
            std::cout << "Выход.\n";
            return 0;
        default:
            std::cerr << "Неизвестный номер задания.\n";
            return 1;
    }

    return 0;
}
