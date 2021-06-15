//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/btos/clock.hpp"
#include "beetree/test-api/gtest-ns.hpp"

namespace bte {
namespace test {
namespace internal {

class TimeEqualsMatcher : public gtest::MatcherInterface<bte::Clock::time_point>
{
public:
    TimeEqualsMatcher(bte::Clock::time_point expected);

    bool MatchAndExplain(bte::Clock::time_point      actual,
                         gtest::MatchResultListener* listener) const override;
    void DescribeTo(std::ostream* os) const override;

private:
    bte::Clock::time_point m_expected;
};
}  // namespace internal
}  // namespace test
}  // namespace bte