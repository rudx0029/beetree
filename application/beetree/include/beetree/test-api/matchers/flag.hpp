//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/btos/flag-types.hpp"
#include "beetree/test-api/gtest-ns.hpp"
#include "internal/flag-equals-matcher.hpp"

namespace bte {
namespace test {
///
/// Matches a Unit of quantity Q for equality against the expected value.
///
/// @tparam Q the unit's quantity
/// @param expected the expected value
/// @return gtest::Matcher<const units::Unit<Q>&>
///
template <class T>
gtest::Matcher<bte::Flag<T>> FlagEquals(bte::Flag<T> expected)
{
    return gtest::MakeMatcher(new internal::FlagEqualsMatcher<T>(expected));
}

}  // namespace test
}  // namespace bte