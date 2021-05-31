//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test-api/matchers/internal/trace-package-equals-matcher.hpp"

namespace bte {
namespace test {
namespace internal {

std::string to_string(const TracePackage& p)
{
    std::string s = "TracePackage{t=[";
    s += std::to_string(p.token.id) + ",";
    s += std::to_string(static_cast<int>(p.channel)) + "]";
    s += ",v=";
    s += std::to_string(static_cast<int>(p.verbosity));
    s += ",a=[";
    for (int i = 0; i < p.num_args; i++)
    {
        if (i) s += ",";
        s += std::to_string(p.args[i]);
    }
    s += "]}";

    return s;
}

TracePackageEqualsMatcher::TracePackageEqualsMatcher(const TracePackage& expected)
    : m_expected(expected)
{}

bool TracePackageEqualsMatcher::MatchAndExplain(const TracePackage&         actual,
                                                gtest::MatchResultListener* listener) const
{
    bool matches =
        m_expected.token.id == actual.token.id && m_expected.channel == actual.channel &&
        m_expected.verbosity == actual.verbosity && m_expected.num_args == actual.num_args;
    for (int i = 0; matches && i < m_expected.num_args; i++)
    {
        matches = (m_expected.args[i] == actual.args[i]);
    }

    if (listener && listener->IsInterested())
    {
        *listener << to_string(actual);
    }

    return matches;
}

void TracePackageEqualsMatcher::DescribeTo(std::ostream* os) const
{
    if (os)
    {
        *os << to_string(m_expected);
    }
}
}  // namespace internal
}  // namespace test
}  // namespace bte