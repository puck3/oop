#include <iostream>
#include <map>
#include <vector>
#include "List.hpp"
#include "Allocator.hpp"

int factorial(int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int main() {
    List<int, Allocator<Node<int>>> l(10, 1);
    List<int, Allocator<Node<int>>> s = {1, 2, 3, 4, 5};
    std::cout << s.front() << " - " << s.back() << std::endl;
    // s.insert(s.end(), 2);
    // for (auto it = s.begin(); it != s.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    std::cout << std::endl;

    std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>, 15>> myMap;
    for (int i = 0; i < 15; ++i) {
        myMap.emplace(i, factorial(i));
    }

    for (const auto& pair : myMap) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
}