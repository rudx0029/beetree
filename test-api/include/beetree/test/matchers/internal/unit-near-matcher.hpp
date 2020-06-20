//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/test/gtest-ns.hpp"
#include "beetree/units/units.hpp"

namespace bte {
namespace test {
namespace internal {

namespace units          = bte::units;
namespace units_internal = bte::units_internal;

template <class Q>
class UnitNearMatcher : public ::testing::MatcherInterface<const units::Unit<Q>&>
{
public:
    UnitNearMatcher(const units::Unit<Q>& expected, const units::Unit<Q>& tolerance)
        : m_expected(expected), m_tolerance(tolerance)
    {}

    bool MatchAndExplain(const units::Unit<Q>&           actual,
                         ::testing::MatchResultListener* listener) const override
    {
        if (listener && listener->IsInterested())
        {
            *listener << std::to_string(units_internal::Real::to_float(actual.as_real()));
        }

        return units::abs(actual - m_expected) <= m_tolerance;
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
    units::Unit<Q> m_tolerance;
};
}  // namespace internal
}  // namespace test
}  // namespace bte