#pragma once

#include <iostream>
#include <queue>
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

template <typename T, typename Container, typename Compare>
void print(std::priority_queue<T, Container, Compare> values) {
    std::vector<T> ordered;
    while (!values.empty()) {
        ordered.push_back(values.top());
        values.pop();
    }
    std::cout << "[\n";
    for (std::size_t i = 0; i < ordered.size(); ++i) {
        std::cout << "  " << ordered[i];
        if (i + 1 != ordered.size()) {
            std::cout << ",";
        }
        std::cout << "\n";
    }
    std::cout << "]" << std::endl;
}

template <typename T>
void print(const std::vector<std::vector<T>>& values) {
    std::cout << "[\n";
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << "  [";
        bool first = true;
        for (const auto& value : values[i]) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << value;
            first = false;
        }
        std::cout << "]";
        if (i + 1 != values.size()) {
            std::cout << ",";
        }
        std::cout << "\n";
    }
    std::cout << "]" << std::endl;
}

}  // namespace leetcode_util
