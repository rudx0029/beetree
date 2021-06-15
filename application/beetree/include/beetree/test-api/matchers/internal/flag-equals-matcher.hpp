//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/btos/flag-types.hpp"
#include "beetree/test-api/gtest-ns.hpp"

namespace bte {
namespace test {
namespace internal {
template <class T>
class FlagEqualsMatcher : public gtest::MatcherInterface<Flag<T>>
{
public:
    FlagEqualsMatcher(Flag<T> expected) : m_expected(expected) {}

    bool MatchAndExplain(Flag<T> actual, gtest::MatchResultListener* listener) const override
    {
        if (listener && listener->IsInterested())
        {
            *listener << std::hex << actual.value;
        }

        return actual.value == m_expected.value;
    }
    void DescribeTo(::std::ostream* os) const override
    {
        if (os)
        {
            *os << std::hex << m_expected.value;
        }
    }

private:
    Flag<T> m_expected;
};
}  // namespace internal
}  // namespace test
}  // namespace bte