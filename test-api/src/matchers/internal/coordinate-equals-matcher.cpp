//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test/matchers/internal/coordinate-equals-matcher.hpp"

namespace bte {
namespace test {
namespace internal {

static std::string to_string(const units::Coordinate& p)
{
    std::string s = "Coord{x=";
    s += std::to_string(p.x.as_real().value);
    s += ",y=";
    s += std::to_string(p.y.as_real().value);
    s += "}";

    return s;
}

CooordinateEqualsMatcher::CooordinateEqualsMatcher(const units::Coordinate& expected)
    : m_expected(expected)
{}

bool CooordinateEqualsMatcher::MatchAndExplain(const units::Coordinate&    actual,
                                               gtest::MatchResultListener* listener) const
{
    bool matches = actual.x == m_expected.x && actual.y == m_expected.y;

    if (listener && listener->IsInterested())
    {
        *listener << to_string(actual);
    }

    return matches;
}

void CooordinateEqualsMatcher::DescribeTo(std::ostream* os) const
{
    if (os)
    {
        *os << to_string(m_expected);
    }
}
}  // namespace internal
}  // namespace test
}  // namespace bte