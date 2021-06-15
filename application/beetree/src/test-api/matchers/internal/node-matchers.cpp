//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test-api/matchers/internal/node-matchers.hpp"
#include <string>

namespace bte {
namespace test {
namespace internal {

std::string to_string(const Exception& ex)
{
    std::string s = "Exception{type=";
    s += std::to_string(static_cast<int>(ex.type()));
    s += ",arg=";
    s += std::to_string(ex.arg());
    s += "}";

    return s;
}

ContextNodeEqualsMatcher::ContextNodeEqualsMatcher(const Node& expected) : m_expected(&expected) {}

bool ContextNodeEqualsMatcher::MatchAndExplain(Context&                    actual,
                                               gtest::MatchResultListener* listener) const
{
    return &actual.get_node() == m_expected;
}

ContextExceptionEqualsMatcher::ContextExceptionEqualsMatcher(const Exception& ex) : m_expected(ex)
{}

bool ContextExceptionEqualsMatcher::MatchAndExplain(Context&                    actual,
                                                    gtest::MatchResultListener* listener) const
{
    bool matches = actual.get_cur_exception().has_value() &&
                   actual.get_cur_exception().value().type() == m_expected.type() &&
                   actual.get_cur_exception().value().arg() == m_expected.arg();

    if (listener && listener->IsInterested())
    {
        *listener << to_string(actual.get_cur_exception().value());
    }

    return matches;
}

void ContextExceptionEqualsMatcher::DescribeTo(std::ostream* os) const
{
    if (os)
    {
        *os << to_string(m_expected);
    }
}

bool ExpectContextExceptionMatcher::MatchAndExplain(Context&                    actual,
                                                    gtest::MatchResultListener* listener) const
{
    if (listener && listener->IsInterested())
    {
        *listener << (actual.get_cur_exception().has_value() ? "actual has exception"
                                                             : "actual does not have exception");
    }

    return actual.get_cur_exception().has_value();
}

void ExpectContextExceptionMatcher::DescribeTo(std::ostream* os) const
{
    if (os)
    {
        *os << "exception expected";
    }
}

bool DoNotExpectContextExceptionMatcher::MatchAndExplain(
    Context&                    actual,
    gtest::MatchResultListener* listener) const
{
    if (listener && listener->IsInterested())
    {
        *listener << (actual.get_cur_exception().has_value() ? "actual has exception"
                                                             : "actual does not have exception");
    }
    return !actual.get_cur_exception().has_value();
}

void DoNotExpectContextExceptionMatcher::DescribeTo(std::ostream* os) const
{
    if (os)
    {
        *os << "exception not expected";
    }
}

}  // namespace internal
}  // namespace test
}  // namespace bte