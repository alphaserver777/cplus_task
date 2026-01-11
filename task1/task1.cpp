#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "task1.hpp"

namespace {

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*') return 2;
    return -1;
}

bool applyOp(std::vector<long long>& values, std::vector<char>& ops, std::string& error) {
    if (values.size() < 2 || ops.empty()) {
        error = "Ошибка в порядке операторов.";
        return false;
    }
    long long b = values.back();
    values.pop_back();
    long long a = values.back();
    values.pop_back();
    char op = ops.back();
    ops.pop_back();

    long long res = 0;
    switch (op) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        default:
            error = "Неизвестный оператор.";
            return false;
    }
    values.push_back(res);
    return true;
}

bool evaluateExpression(const std::string& expr, long long& result, std::string& error) {
    std::vector<long long> values;
    std::vector<char> ops;
    bool expectNumber = true;  // true после '(' или в начале — допускаем унарный минус

    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (std::isspace(static_cast<unsigned char>(c))) continue;

        if (std::isdigit(static_cast<unsigned char>(c)) ||
            (c == '-' && expectNumber && i + 1 < expr.size() &&
             std::isdigit(static_cast<unsigned char>(expr[i + 1])))) {
            // Число (возможно, с унарным минусом).
            bool negative = false;
            if (c == '-') {
                negative = true;
                ++i;
            }
            long long value = 0;
            for (; i < expr.size() && std::isdigit(static_cast<unsigned char>(expr[i])); ++i) {
                value = value * 10 + (expr[i] - '0');
            }
            --i;  // цикл for увеличит ещё раз
            values.push_back(negative ? -value : value);
            expectNumber = false;
        } else if (c == '(') {
            ops.push_back(c);
            expectNumber = true;
        } else if (c == ')') {
            while (!ops.empty() && ops.back() != '(') {
                if (!applyOp(values, ops, error)) return false;
            }
            if (ops.empty()) {
                error = "Лишняя закрывающая скобка.";
                return false;
            }
            ops.pop_back();  // убираем '('
            expectNumber = false;
        } else if (c == '+' || c == '-' || c == '*') {
            while (!ops.empty() && precedence(ops.back()) >= precedence(c)) {
                if (!applyOp(values, ops, error)) return false;
            }
            ops.push_back(c);
            expectNumber = true;
        } else {
            error = std::string("Недопустимый символ: ") + c;
            return false;
        }
    }

    while (!ops.empty()) {
        if (ops.back() == '(') {
            error = "Не хватает закрывающей скобки.";
            return false;
        }
        if (!applyOp(values, ops, error)) return false;
    }

    if (values.size() != 1) {
        error = "Неверная структура выражения.";
        return false;
    }

    result = values.back();
    return true;
}

}  // namespace

void runTask1() {
    std::cout << "Введите арифметическое выражение (+, -, *, скобки, целые числа):\n> ";
    std::string expr;
    std::getline(std::cin, expr);

    long long result = 0;
    std::string error;
    if (evaluateExpression(expr, result, error)) {
        std::cout << "Результат: " << result << "\n";
    } else {
        std::cout << "Ошибка: " << error << "\n";
    }
}
