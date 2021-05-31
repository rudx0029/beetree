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
namespace internal {

class CooordinateEqualsMatcher : public gtest::MatcherInterface<const units::Coordinate&>
{
public:
    CooordinateEqualsMatcher(const units::Coordinate& expected);

    bool MatchAndExplain(const units::Coordinate&    actual,
                         gtest::MatchResultListener* listener) const override;
    void DescribeTo(std::ostream* os) const override;

private:
    units::Coordinate m_expected;
};

}  // namespace internal
}  // namespace test
}  // namespace bte