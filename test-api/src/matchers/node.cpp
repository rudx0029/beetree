//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test/matchers/node.hpp"
#include "beetree/test/matchers/internal/node-matchers.hpp"

namespace bte {
namespace test {

gtest::Matcher<Context&> ContextNodeEquals(const Node& expected)
{
    return gtest::MakeMatcher(new internal::ContextNodeEqualsMatcher(expected));
}

gtest::Matcher<Context&> ContextExceptionEquals(const Exception& expected)
{
    return gtest::MakeMatcher(new internal::ContextExceptionEqualsMatcher(expected));
}

gtest::Matcher<Context&> ExpectContextException()
{
    return gtest::MakeMatcher(new internal::ExpectContextExceptionMatcher());
}

gtest::Matcher<Context&> DoNotExpectContextException()
{
    return gtest::MakeMatcher(new internal::DoNotExpectContextExceptionMatcher());
}

}  // namespace test
}  // namespace bte
