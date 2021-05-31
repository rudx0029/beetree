//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/units/motion-profile.hpp"

namespace bte {
namespace test {
namespace internal {

class MotionProfileEqualsMatcher : public gtest::MatcherInterface<units::MotionProfile>
{
public:
    MotionProfileEqualsMatcher(units::MotionProfile expected);

    bool MatchAndExplain(units::MotionProfile        actual,
                         gtest::MatchResultListener* listener) const override;
    void DescribeTo(std::ostream* os) const override;

private:
    units::MotionProfile m_expected;
};
}  // namespace internal
}  // namespace test
}  // namespace bte