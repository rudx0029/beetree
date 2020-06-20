//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/context.hpp"
#include "beetree/test/gtest-ns.hpp"

namespace bte {
namespace test {
///
/// Matches a trees expected node to the node provided in the run-time context
/// @param expected the expected node
/// @return the matcher
///
gtest::Matcher<Context&> ContextNodeEquals(const Node& expected);
///
/// Matches an expected exception to the exception provided in the run-time context
/// @param expected the expected exception
/// @return the matcher
///
gtest::Matcher<Context&> ContextExceptionEquals(const Exception& expected);

///
/// Matcher that expects the exception provided by the node's run-time context
/// to be available.
/// @return the matcher
///
gtest::Matcher<Context&> ExpectContextException();

///
/// Matcher that does not expect the exception provided by the node's run-time
/// context to be available.
/// @return the matcher
///
gtest::Matcher<Context&> DoNotExpectContextException();

}  // namespace test
}  // namespace bte
