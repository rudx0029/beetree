//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/units/units.hpp"
#include "gmock/gmock.h"

namespace bte {
namespace test {
namespace internal {

namespace units          = bte::units;
namespace units_internal = bte::units_internal;

template <class Q>
class UnitMatcher : public gtest::MatcherInterface<units::Unit<Q>>
{
public:
    UnitMatcher(units::Unit<Q> expected) : m_expected(expected) {}

    bool MatchAndExplain(units::Unit<Q>              actual,
                         gtest::MatchResultListener* listener) const override
    {
        if (listener && listener->IsInterested())
        {
            *listener << to_string(actual);
        }

        return test(actual, m_expected);
    }
    void DescribeTo(::std::ostream* os) const override
    {
        if (os)
        {
            *os << to_string(m_expected);
        }
    }

protected:
    virtual bool test(units::Unit<Q> actual, units::Unit<Q> expected) const = 0;

private:
    std::string to_string(units::Unit<Q> u) const
    {
        return std::to_string(units_internal::Real::to_float(u.as_real()));
    }

    units::Unit<Q> m_expected;
};

template <class Q>
class UnitGtMatcher : public UnitMatcher<Q>
{
public:
    UnitGtMatcher(units::Unit<Q> expected) : UnitMatcher<Q>(expected) {}

    bool test(units::Unit<Q> actual, units::Unit<Q> expected) const override
    {
        return actual > expected;
    }
};

template <class Q>
class UnitGtEqMatcher : public UnitMatcher<Q>
{
public:
    UnitGtEqMatcher(units::Unit<Q> expected) : UnitMatcher<Q>(expected) {}

    bool test(units::Unit<Q> actual, units::Unit<Q> expected) const override
    {
        return actual >= expected;
    }
};

template <class Q>
class UnitLtEqMatcher : public UnitMatcher<Q>
{
public:
    UnitLtEqMatcher(units::Unit<Q> expected) : UnitMatcher<Q>(expected) {}

    bool test(units::Unit<Q> actual, units::Unit<Q> expected) const override
    {
        return actual <= expected;
    }
};

template <class Q>
class UnitLtMatcher : public UnitMatcher<Q>
{
public:
    UnitLtMatcher(units::Unit<Q> expected) : UnitMatcher<Q>(expected) {}

    bool test(units::Unit<Q> actual, units::Unit<Q> expected) const override
    {
        return actual < expected;
    }
};

}  // namespace internal
}  // namespace test
}  // namespace bte