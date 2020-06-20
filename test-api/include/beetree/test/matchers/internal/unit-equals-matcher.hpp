//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/units/units.hpp"
#include "gmock/gmock.h"

namespace bte {
namespace test {
namespace internal {

namespace units          = bte::units;
namespace units_internal = bte::units_internal;

///
/// Unit Equals Matcher Backend
///
/// @tparam Q
///
template <class Q>
class UnitEqualsMatcher : public ::testing::MatcherInterface<const units::Unit<Q>&>
{
public:
    UnitEqualsMatcher(const units::Unit<Q>& expected) : m_expected(expected) {}

    bool MatchAndExplain(const units::Unit<Q>&           actual,
                         ::testing::MatchResultListener* listener) const override
    {
        if (listener && listener->IsInterested())
        {
            *listener << std::to_string(units_internal::Real::to_float(actual.as_real()));
        }

        return actual == m_expected;
    }
    void DescribeTo(::std::ostream* os) const override
    {
        if (os)
        {
            *os << std::to_string(units_internal::Real::to_float(m_expected.as_real()));
        }
    }

private:
    units::Unit<Q> m_expected;
};
}  // namespace internal
}  // namespace test
}  // namespace bte