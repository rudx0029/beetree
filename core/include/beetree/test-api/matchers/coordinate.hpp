//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/units/coordinate.hpp"

namespace bte {
namespace test {
///
/// Matches a coordinate to be equal with the expected
/// @param expected the expected coordinate
/// @return the matcher
///
gtest::Matcher<const units::Coordinate&> CoordinateEquals(const units::Coordinate& expected);

///
/// Matches a coordinate to be euqal with the expected pose.
///
/// @param expected the expected coordinate as a 2D Pose.
/// @return the matcher
///
gtest::Matcher<const units::Coordinate&> CoordinateEquals(const units::Pose2D& expected);

}  // namespace test
}  // namespace bte
