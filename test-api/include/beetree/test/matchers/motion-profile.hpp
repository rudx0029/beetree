//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/test/gtest-ns.hpp"
#include "beetree/units/motion-profile.hpp"

namespace bte {
namespace test {
///
/// Matches a motion profile to be equal to the expected
/// @param expected the expected pose
/// @return the matcher
///
gtest::Matcher<units::MotionProfile> MotionProfileEquals(units::MotionProfile expected);

}  // namespace test
}  // namespace bte
