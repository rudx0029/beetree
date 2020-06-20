//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/context.hpp"
#include "beetree/engine/exception.hpp"
#include "beetree/engine/node.hpp"
#include "beetree/engine/recipe.hpp"
#include "beetree/engine/result.hpp"
#include "beetree/test/gtest-ns.hpp"
#include "beetree/trace/trace.hpp"

namespace bte {
namespace test {

/// Basic actions to support mocking a node through GMock
/// The actions reflect node's recipe.
class IActions
{
public:
    virtual void   setup(Context&)                          = 0;
    virtual Result loop(Context&)                           = 0;
    virtual void   teardown(Context&)                       = 0;
    virtual void   on_exception(const Exception&, Context&) = 0;
    virtual void   on_branch_complete(Status, Context&)     = 0;
    virtual void   on_trace(TraceStream&, Context&)         = 0;
};

/// The mockable class of node actions ... see above
class MockActions : public IActions
{
public:
    MOCK_METHOD1(setup, void(Context&));
    MOCK_METHOD1(loop, Result(Context&));
    MOCK_METHOD1(teardown, void(Context&));

    MOCK_METHOD2(on_exception, void(const Exception&, Context&));
    MOCK_METHOD2(on_branch_complete, void(Status, Context&));
    MOCK_METHOD2(on_trace, void(TraceStream&, Context&));

    MockActions() {}
};

namespace internal {
void   install_actions(int id, IActions& actions);
void   setup_mock_node(Context&, int id);
Recipe mock_node_recipe(delegate::Setup setup);
}  // namespace internal

///
/// A compositional class that combines the mock actions and its
/// meta node. The ID is used to look up the actions during unit test
/// when the engine encounters the node. This enables a 1-1 pairing of
/// the node and its mock actions.
///
/// @tparam ID The id of the mock node used to look up its mock actions
/// given its recipe fnc mock_node_recipe<ID>
///
/// @tparam USE_STRICT Use ::testing::StrictMock for the MockActions
///
template <int ID = 0, bool USE_STRICT = false>
class MockNode
{
    // private:
    static void   setup(Context& c) { internal::setup_mock_node(c, ID); }
    static Recipe recipe() { return internal::mock_node_recipe(MockNode<ID, USE_STRICT>::setup); }

public:
    // > Properties
    gtest::NiceMock<MockActions> actions;
    Node                         node{MockNode<ID, USE_STRICT>::recipe};

    // > Constructors
    MockNode() { internal::install_actions(ID, actions); }
};

template <int ID>
class MockNode<ID, true>
{
    // private:
    static void   setup(Context& c) { internal::setup_mock_node(c, ID); }
    static Recipe recipe() { return internal::mock_node_recipe(MockNode<ID, true>::setup); }

public:
    // > Properties
    gtest::StrictMock<MockActions> actions;
    Node                           node{MockNode<ID, true>::recipe};

    // > Constructors
    MockNode() { internal::install_actions(ID, actions); }
};

}  // namespace test
}  // namespace bte