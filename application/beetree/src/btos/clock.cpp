#include "beetree/btos/clock.hpp"

namespace bte {
static Clock::fnc_now_t s_now_fnc = chrono::now_ms;

Clock::time_point Clock::now() noexcept { return Clock::time_point{Clock::duration{s_now_fnc()}}; }

Clock::duration Clock::elapsed(const Clock::time_point& start) { return Clock::now() - start; }

void Clock::set_now_fnc(fnc_now_t now_fnc)
{
    if (now_fnc != nullptr)
    {
        s_now_fnc = now_fnc;
    }
}
}  // namespace bte