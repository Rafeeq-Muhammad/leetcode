#pragma once

#include "includes.hpp"
#include "print.hpp"

using namespace std;  // NOLINT
using namespace leetcode_util;  // NOLINT

namespace leetcode_util::detail {

inline void util_anchor() {
    (void)includes_anchor_ref;
}

[[maybe_unused]] inline auto util_anchor_ref = (util_anchor(), 0);

}  // namespace leetcode_util::detail
