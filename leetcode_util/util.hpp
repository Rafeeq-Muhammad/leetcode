#pragma once

#include "includes.hpp"
#include "print.hpp"

using namespace std;  // NOLINT
using namespace leetcode_util;  // NOLINT

namespace leetcode_util {

template <typename T>
constexpr T Max(T value) {
    return value;
}

template <typename T, typename... Ts>
constexpr auto Max(T value, Ts... values) -> std::common_type_t<T, Ts...> {
    using Result = std::common_type_t<T, Ts...>;
    Result result = static_cast<Result>(value);
    ((result = result < static_cast<Result>(values) ? static_cast<Result>(values) : result), ...);
    return result;
}

template <typename T>
constexpr T Min(T value) {
    return value;
}

template <typename T, typename... Ts>
constexpr auto Min(T value, Ts... values) -> std::common_type_t<T, Ts...> {
    using Result = std::common_type_t<T, Ts...>;
    Result result = static_cast<Result>(value);
    ((result = result > static_cast<Result>(values) ? static_cast<Result>(values) : result), ...);
    return result;
}

}  // namespace leetcode_util

namespace leetcode_util::detail {

inline void util_anchor() {
    (void)includes_anchor_ref;
}

[[maybe_unused]] inline auto util_anchor_ref = (util_anchor(), 0);

}  // namespace leetcode_util::detail
