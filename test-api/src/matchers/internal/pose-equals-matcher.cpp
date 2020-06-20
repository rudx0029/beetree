//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test/matchers/internal/pose-equals-matcher.hpp"

namespace bte {
namespace test {
namespace internal {

std::string to_string(const units::Pose2D& p)
{
    std::string s = "Pose2D{x=";
    s += std::to_string(p.x.as_real().value);
    s += ",y=";
    s += std::to_string(p.y.as_real().value);
    s += ",heading=";
    s += std::to_string(p.heading.as_real().value);
    s += "}";

    return s;
}

PoseEqualsMatcher::PoseEqualsMatcher(const units::Pose2D& expected) : m_expected(expected) {}

bool PoseEqualsMatcher::MatchAndExplain(const units::Pose2D&        actual,
                                        gtest::MatchResultListener* listener) const
{
    bool matches = actual.x == m_expected.x && actual.y == m_expected.y &&
                   actual.heading == m_expected.heading;

    if (listener && listener->IsInterested())
    {
        *listener << to_string(actual);
    }

    return matches;
}

void PoseEqualsMatcher::DescribeTo(std::ostream* os) const
{
    if (os)
    {
        *os << to_string(m_expected);
    }
}

}  // namespace internal
}  // namespace test
}  // namespace bte