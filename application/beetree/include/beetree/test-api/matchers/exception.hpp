//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "beetree/engine/exception.hpp"
#include "beetree/units/coordinate.hpp"
#include "beetree/units/pose-2d.hpp"
#include "beetree/units/units.hpp"

namespace bte {
namespace test {
///
/// Matches an exception to have the same type as the expected
///
MATCHER_P(ExceptionTypeEquals, expected, "") { return arg.type() == expected.type(); }
///
/// Matches an exception to have the same type and argument as the expected
///
MATCHER_P(ExceptionEquals, expected, "")
{
    return arg.type() == expected.type() && arg.arg() == expected.arg();
}

}  // namespace test
}  // namespace bte
