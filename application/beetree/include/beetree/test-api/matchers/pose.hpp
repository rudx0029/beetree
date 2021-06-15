//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/units/pose-2d.hpp"

namespace bte {
namespace test {

///
/// Matches a pose to be equal to the expected
/// @param expected the expected pose
/// @return the matcher
///
gtest::Matcher<const units::Pose2D&> PoseEquals(const units::Pose2D& expected);

}  // namespace test
}  // namespace bte
