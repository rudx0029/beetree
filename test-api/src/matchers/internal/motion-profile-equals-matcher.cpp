//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test/matchers/internal/motion-profile-equals-matcher.hpp"

namespace bte {
namespace test {
namespace internal {

std::string to_string(const units::MotionProfile& p)
{
    std::string s = "MotionProfile{v=";
    s += std::to_string(p.velocity.as_real().value);
    s += ",a=";
    s += std::to_string(p.acceleration.as_real().value);
    s += ",w=";
    s += std::to_string(p.angularVelocity.as_real().value);
    s += "}";

    return s;
}

MotionProfileEqualsMatcher::MotionProfileEqualsMatcher(units::MotionProfile expected)
    : m_expected(expected)
{}

bool MotionProfileEqualsMatcher::MatchAndExplain(units::MotionProfile        actual,
                                                 gtest::MatchResultListener* listener) const
{
    bool matches = actual.acceleration == m_expected.acceleration &&
                   actual.angularVelocity == m_expected.angularVelocity &&
                   actual.velocity == m_expected.velocity;

    if (listener && listener->IsInterested())
    {
        *listener << to_string(actual);
    }

    return matches;
}

void MotionProfileEqualsMatcher::DescribeTo(std::ostream* os) const
{
    if (os)
    {
        *os << to_string(m_expected);
    }
}
}  // namespace internal
}  // namespace test
}  // namespace bte