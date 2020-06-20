//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test/matchers/pose.hpp"
#include "beetree/test/matchers/internal/pose-equals-matcher.hpp"

namespace bte {
namespace test {

gtest::Matcher<const units::Pose2D&> PoseEquals(const units::Pose2D& expected)
{
    return gtest::MakeMatcher(new internal::PoseEqualsMatcher(expected));
}

}  // namespace test
}  // namespace bte
