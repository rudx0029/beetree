//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test-api/matchers/trace-package.hpp"
#include "beetree/test-api/matchers/internal/trace-package-equals-matcher.hpp"

namespace bte {
namespace test {

gtest::Matcher<const TracePackage&> TracePackageEquals(const TracePackage& expected)
{
    return gtest::MakeMatcher(new internal::TracePackageEqualsMatcher(expected));
}

}  // namespace test
}  // namespace bte
