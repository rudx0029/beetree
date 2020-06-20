//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include <chrono>
#include "beetree/platform/i-system-clock.hpp"

namespace bte {
struct Clock
{
    // chrono required fields
    using rep        = chrono::timepoint_ms;
    using period     = std::milli;
    using duration   = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<Clock>;

    // aliases
    using milliseconds = duration;
    using ms           = duration;
    using tp           = time_point;

    static constexpr bool is_steady = true;
    // additional
    using fnc_now_t = rep (*)(void);

    static time_point now() noexcept;
    static duration   elapsed(const time_point& start);
    static void       set_now_fnc(fnc_now_t now_fnc);
};
}  // namespace bte