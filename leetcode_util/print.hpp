#pragma once

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

namespace leetcode_util {

// Forward declarations
namespace detail {
    template <typename T>
    void print_value(std::ostream& os, const T& value);

    template <typename T>
    void print_value(std::ostream& os, const std::vector<T>& values);

    template <typename T, typename Container, typename Compare>
    void print_value(std::ostream& os, std::priority_queue<T, Container, Compare> values);

    template <typename T>
    void print_value(std::ostream& os, const std::vector<std::vector<T>>& values);

    template <typename K, typename V>
    void print_value(std::ostream& os, const std::unordered_map<K, V>& map);
    
    template <typename T, typename... Ts>
    void print_impl(std::ostream& os, const T& first, const Ts&... rest);
    
    inline void print_impl(std::ostream& os);
}

// The main entry point for printing.
// Handles single and multiple arguments.
template <typename... Ts>
void print(const Ts&... args) {
    detail::print_impl(std::cout, args...);
    std::cout << std::endl;
}

namespace detail {
    // These helpers do the actual printing to the stream without a newline.
    template <typename T>
    void print_value(std::ostream& os, const T& value) {
        os << value;
    }

    template <typename T>
    void print_value(std::ostream& os, const std::vector<T>& values) {
        os << "[";
        bool first = true;
        for (const auto& value : values) {
            if (!first) {
                os << ", ";
            }
            print_value(os, value); // Recursive call
            first = false;
        }
        os << "]";
    }

    template <typename T, typename Container, typename Compare>
    void print_value(std::ostream& os, std::priority_queue<T, Container, Compare> values) {
        std::vector<T> ordered;
        while (!values.empty()) {
            ordered.push_back(values.top());
            values.pop();
        }
        os << '[' << '\n';
        for (std::size_t i = 0; i < ordered.size(); ++i) {
            os << "  ";
            print_value(os, ordered[i]);
            if (i + 1 != ordered.size()) {
                os << ",";
            }
            os << '\n';
        }
        os << "]";
    }

    template <typename T>
    void print_value(std::ostream& os, const std::vector<std::vector<T>>& values) {
        os << '[' << '\n';
        for (std::size_t i = 0; i < values.size(); ++i) {
            os << "  [";
            bool first = true;
            for (const auto& value : values[i]) {
                if (!first) {
                    os << ", ";
                }
                print_value(os, value);
                first = false;
            }
            os << "]";
            if (i + 1 != values.size()) {
                os << ",";
            }
            os << '\n';
        }
        os << "]";
    }

    template <typename K, typename V>
    void print_value(std::ostream& os, const std::unordered_map<K, V>& map) {
        os << "{";
        bool first = true;
        for (const auto& pair : map) {
            if (!first) {
                os << ", ";
            }
            print_value(os, pair.first);
            os << ": ";
            print_value(os, pair.second);
            first = false;
        }
        os << "}";
    }

    // Base case for the recursive print_impl
    inline void print_impl(std::ostream& os) {}

    // The recursive part of the main print function
    template <typename T, typename... Ts>
    void print_impl(std::ostream& os, const T& first, const Ts&... rest) {
        print_value(os, first);
        if constexpr (sizeof...(rest) > 0) {
            os << " ";
            print_impl(os, rest...);
        }
    }
} // namespace detail

}  // namespace leetcode_util

#define dprint(var) \
    do { \
        std::cout << #var << ": "; \
        leetcode_util::detail::print_impl(std::cout, var); \
        std::cout << std::endl; \
    } while (0)
