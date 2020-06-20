//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test/matchers/motion-profile.hpp"
#include "beetree/test/matchers/internal/motion-profile-equals-matcher.hpp"

namespace bte {
namespace test {

gtest::Matcher<units::MotionProfile> MotionProfileEquals(units::MotionProfile expected)
{
    return gtest::MakeMatcher(new internal::MotionProfileEqualsMatcher(expected));
}

}  // namespace test
}  // namespace bte
