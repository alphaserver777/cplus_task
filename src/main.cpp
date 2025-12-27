#include <iostream>
#include <limits>
#include "tasks.hpp"

int main() {
    std::cout << "Учебный проект (C++) — выберите задание:\n";
    std::cout << "1. Вычисление арифметического выражения\n";
    std::cout << "2. Операции со множеством из файла\n";
    std::cout << "3. Разбиение множества на равные суммы\n";
    std::cout << "4. Все подмножества массива\n";
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
            runExpressionEvaluator();
            break;
        case 2:
            runSetOperations();
            break;
        case 3:
            runPartitionDemo();
            break;
        case 4:
            runSubsetsDemo();
            break;
        case 5:
            runAvlBalanceDemo();
            break;
        case 6:
            runHashTableDemo();
            break;
        case 7:
            runGenealogyDemo();
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
