//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/test/gtest-ns.hpp"
#include "beetree/trace/trace-defs.hpp"

namespace bte {
namespace test {
namespace internal {

class TracePackageEqualsMatcher : public gtest::MatcherInterface<const TracePackage&>
{
public:
    TracePackageEqualsMatcher(const TracePackage& expected);

    bool MatchAndExplain(const TracePackage&         actual,
                         gtest::MatchResultListener* listener) const override;
    void DescribeTo(std::ostream* os) const override;

private:
    TracePackage m_expected;
};
}  // namespace internal
}  // namespace test
}  // namespace bte