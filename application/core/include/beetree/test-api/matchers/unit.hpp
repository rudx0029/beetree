//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/test-api/matchers/internal/unit-comparison-matchers.hpp"
#include "beetree/test-api/matchers/internal/unit-equals-matcher.hpp"
#include "beetree/test-api/matchers/internal/unit-near-matcher.hpp"
#include "beetree/units/units.hpp"

namespace bte {
namespace test {

///
/// Matches a Unit of quantity Q for equality against the expected value.
///
/// @tparam Q the unit's quantity
/// @param expected the expected value
/// @return gtest::Matcher<const units::Unit<Q>&>
///
template <class Q>
gtest::Matcher<const units::Unit<Q>&> UnitEquals(const units::Unit<Q>& expected)
{
    return gtest::MakeMatcher(new internal::UnitEqualsMatcher<Q>(expected));
}
///
/// Matches a Unit of Quantity Q to be within tolerance.
///
/// @tparam Q
/// @param expected
/// @param tolerance
/// @return gtest::Matcher<const units::Unit<Q>&>
///
template <class Q>
gtest::Matcher<const units::Unit<Q>&> UnitNear(const units::Unit<Q>& expected,
                                               const units::Unit<Q>& tolerance)
{
    return gtest::MakeMatcher(new internal::UnitNearMatcher<Q>(expected, tolerance));
}

template <class Q>
gtest::Matcher<units::Unit<Q>> UnitGt(units::Unit<Q> expected)
{
    return gtest::MakeMatcher(new internal::UnitGtMatcher<Q>(expected));
}

template <class Q>
gtest::Matcher<units::Unit<Q>> UnitGtEq(units::Unit<Q> expected)
{
    return gtest::MakeMatcher(new internal::UnitGtEqMatcher<Q>(expected));
}

template <class Q>
gtest::Matcher<units::Unit<Q>> UnitLtEq(units::Unit<Q> expected)
{
    return gtest::MakeMatcher(new internal::UnitLtEqMatcher<Q>(expected));
}

template <class Q>
gtest::Matcher<units::Unit<Q>> UnitLt(units::Unit<Q> expected)
{
    return gtest::MakeMatcher(new internal::UnitLtMatcher<Q>(expected));
}

///
/// @deprecated
/// compares the real number arg against the expected for equality
///
MATCHER_P(IsRealEqualTo, value, "") { return arg == value; }
///
/// @deprecated
/// compares the real number arg against the expected to be within the the
/// tolerance
///
MATCHER_P2(IsRealNearTo, value, tolerance, "")
{
    return units_internal::RealMath::abs(arg - value) < tolerance;
}

}  // namespace test
}  // namespace bte