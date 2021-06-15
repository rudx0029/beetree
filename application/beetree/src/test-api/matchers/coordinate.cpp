//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/test-api/matchers/coordinate.hpp"
#include "beetree/test-api/matchers/internal/coordinate-equals-matcher.hpp"
#include "beetree/units/methods.hpp"

namespace bte {
namespace test {

gtest::Matcher<const units::Coordinate&> CoordinateEquals(const units::Coordinate& expected)
{
    return gtest::MakeMatcher(new internal::CooordinateEqualsMatcher(expected));
}

gtest::Matcher<const units::Coordinate&> CoordinateEquals(const units::Pose2D& expected)
{
    return gtest::MakeMatcher(new internal::CooordinateEqualsMatcher(units::to_coord(expected)));
}

}  // namespace test
}  // namespace bte
