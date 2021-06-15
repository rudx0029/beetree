#pragma once

#include "beetree/btos/clock.hpp"
#include "beetree/units/units.hpp"

namespace bte {
class SimpleBumpFilter
{
public:
    bool apply(bool input_bump);

private:
    bool              m_last_bump;
    Clock::time_point m_since_last_bump{0_ms};
};
}  // namespace bte