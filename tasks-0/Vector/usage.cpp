#include "Vector.hpp"
#include <string>
#include <algorithm>
#include <iostream>

int main() {
    // String test
    std::cout << "  === String test ===\n";

    Vector<std::string> str_vec(3);
    str_vec[0] = "hello";
    str_vec[1] = "everyone";
    str_vec[2] = "!";

    std::cout << "[0]: " << str_vec[0] << "\nElemets count: " << str_vec.size() << "\n";
    str_vec.erase(str_vec.begin());
    std::cout << "[0]: " << str_vec[0] << "\nElemets count: " << str_vec.size() << "\n\n\n";

    // Sort test
    std::cout << "  === Sort test ===\n";

    Vector<int> ints(10);
    for (int i = 0; i < 10; ++i) {
        ints.at(i) = 10 - i;
        std::cout << ints[i] << " ";
    }

    std::cout << "\n\nInsert 4:\n";
    ints.insert(ints.begin(), 4);
    for (int i = 0; i < ints.size(); ++i) {
        std::cout << ints[i] << " ";
    }

    std::cout << "\n\nPush back 7:\n";
    ints.push_back(7);
    for (int i = 0; i < ints.size(); ++i) {
        std::cout << ints[i] << " ";
    }

    std::cout << "\n\nDouble pop back:\n";
    ints.pop_back();
    ints.pop_back();
    for (int i = 0; i < ints.size(); ++i) {
        std::cout << ints[i] << " ";
    }
    
    std::cout << "\n\nSort:\n";
    std::sort(ints.begin(), ints.end());
    for (int i = 0; i < ints.size(); ++i) {
        std::cout << ints[i] << " ";
    }

    return 0;
}