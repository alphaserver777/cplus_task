#include <iostream>
#include <limits>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "tasks.hpp"

namespace {

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

int countDescendants(const std::string& name, const Graph& tree,
                     std::unordered_map<std::string, int>& memo) {
    auto it = memo.find(name);
    if (it != memo.end()) return it->second;
    int total = 0;
    auto chIt = tree.find(name);
    if (chIt != tree.end()) {
        for (const auto& child : chIt->second) {
            total += 1 + countDescendants(child, tree, memo);
        }
    }
    memo[name] = total;
    return total;
}

}  // namespace

void runGenealogyDemo() {
    std::cout << "Количество элементов в генеалогическом древе: ";
    int n = 0;
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Нужно положительное число.\n";
        return;
    }

    Graph tree;
    std::set<std::string> allNames;
    std::cout << "Введите " << (n - 1) << " строк вида <потомок> <родитель>:\n";
    for (int i = 0; i < n - 1; ++i) {
        std::string child, parent;
        std::cin >> child >> parent;
        tree[parent].push_back(child);
        allNames.insert(child);
        allNames.insert(parent);
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::unordered_map<std::string, int> memo;
    std::cout << "Результат (лексикографически):\n";
    for (const auto& name : allNames) {
        int cnt = countDescendants(name, tree, memo);
        std::cout << name << " " << cnt << "\n";
    }
}
