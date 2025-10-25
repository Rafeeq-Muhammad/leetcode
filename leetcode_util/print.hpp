#pragma once

#include <iostream>
#include <vector>

namespace leetcode_util {

// Prints any value that supports operator<< followed by a newline.
template <typename T>
void print(const T& value) {
    std::cout << value << std::endl;
}

// Prints a vector to std::cout in a compact, readable format.
template <typename T>
void print(const std::vector<T>& values) {
    std::cout << "[";
    bool first = true;
    for (const auto& value : values) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << value;
        first = false;
    }
    std::cout << "]" << std::endl;
}

}  // namespace leetcode_util
