//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/test-api/matchers/time.hpp"
#include "beetree/test-api/matchers/internal/time-equals-matcher.hpp"

namespace bte {
namespace test {

///
/// Matches a time point to be equal with the expected
/// @param expected the expected time point
/// @return the matcher
///
gtest::Matcher<Clock::time_point> TimeEquals(Clock::time_point expected)
{
    return gtest::MakeMatcher(new internal::TimeEqualsMatcher(expected));
}

///
/// Matches a coordinate to be euqal with the expected pose.
///
/// @param expected the expected time point expressed as a uint32_t
/// @return the matcher
///
gtest::Matcher<Clock::time_point> TimeEquals(uint32_t expected)
{
    auto expected_tp = Clock::time_point{Clock::ms{expected}};
    return gtest::MakeMatcher(new internal::TimeEqualsMatcher(expected_tp));
}

}  // namespace test
}  // namespace bte
