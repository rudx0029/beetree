//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test-api/matchers/internal/time-equals-matcher.hpp"

namespace bte {
namespace test {
namespace internal {

using time_point = bte::Clock::time_point;

static std::string to_string(time_point tp)
{
    return std::to_string(tp.time_since_epoch().count()) + " ms";
}

TimeEqualsMatcher::TimeEqualsMatcher(time_point expected) : m_expected(expected) {}

bool TimeEqualsMatcher::MatchAndExplain(time_point                  actual,
                                        gtest::MatchResultListener* listener) const
{
    if (listener && listener->IsInterested())
    {
        *listener << to_string(actual);
    }

    return actual == m_expected;
}

void TimeEqualsMatcher::DescribeTo(std::ostream* os) const
{
    if (os)
    {
        *os << to_string(m_expected);
    }
}

}  // namespace internal
}  // namespace test
}  // namespace bte