//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/context.hpp"
#include "beetree/test-api/gtest-ns.hpp"

namespace bte {
namespace test {
namespace internal {

class ContextNodeEqualsMatcher : public gtest::MatcherInterface<bte::Context&>
{
public:
    ContextNodeEqualsMatcher(const bte::Node& expected);

    bool MatchAndExplain(bte::Context&               actual,
                         gtest::MatchResultListener* listener) const override;
    void DescribeTo(std::ostream* os) const override {}

private:
    const bte::Node* m_expected = nullptr;
};

class ContextExceptionEqualsMatcher : public gtest::MatcherInterface<bte::Context&>
{
public:
    ContextExceptionEqualsMatcher(const bte::Exception& expected);

    bool MatchAndExplain(bte::Context&               actual,
                         gtest::MatchResultListener* listener) const override;
    void DescribeTo(std::ostream* os) const override;

private:
    bte::Exception m_expected;
};

class ExpectContextExceptionMatcher : public gtest::MatcherInterface<bte::Context&>
{
public:
    ExpectContextExceptionMatcher() = default;

    bool MatchAndExplain(bte::Context&               actual,
                         gtest::MatchResultListener* listener) const override;
    void DescribeTo(std::ostream* os) const override;
};

class DoNotExpectContextExceptionMatcher : public gtest::MatcherInterface<bte::Context&>
{
public:
    DoNotExpectContextExceptionMatcher() = default;

    bool MatchAndExplain(bte::Context&               actual,
                         gtest::MatchResultListener* listener) const override;
    void DescribeTo(std::ostream* os) const override;
};

}  // namespace internal
}  // namespace test
}  // namespace bte