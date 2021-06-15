#include "beetree/facilities/filters/simple-bump-filter.hpp"

namespace bte {

bool SimpleBumpFilter::apply(bool current_bump)
{
    bool is_bumped = false;
    if (Clock::elapsed(m_since_last_bump) >= 500_ms)
    {
        is_bumped   = (current_bump != m_last_bump) && current_bump;
        m_last_bump = current_bump;

        if (is_bumped)
        {
            m_since_last_bump = Clock::now();
        }
    }
    return is_bumped;
}
}  // namespace bte