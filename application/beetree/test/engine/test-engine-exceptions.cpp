//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/engine/engine.hpp"
#include "beetree/engine/try-catch.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/test-api/matchers/exception.hpp"
#include "beetree/test-api/matchers/node.hpp"
#include "beetree/test-api/mocks/mock-node.hpp"
#include "beetree/test-api/mocks/platform-mock.hpp"

using namespace bte;
using namespace bte::test;

using gtest::_;
using gtest::Return;

class EngineExceptionsTest : public BehaviorReqTest
{
protected:
    // > Mock Try Catch Tree
    PlatformMock platform;  // for mocking time
    MockNode<0>  root;
    MockNode<1>  mock_try;
    MockNode<2>  mock_catch;

    // try catch tree
    Branches<2> branches = {&mock_try.node, &mock_catch.node};
    Node        try_catch{try_catch_all, branches};

    // > Engine
    Engine                       engine;
    static constexpr std::size_t stack_len = 256;
    uint8_t                      stack[stack_len];
    Exception                    expected_ex{bte::ExceptionType::USER, 123};

    static void SetUpTestCase() { Feature("beetree"); }
    void        SetUp() override
    {
        engine.configure(&root.node, stack, stack_len);

        ON_CALL(root.actions, loop(ContextNodeEquals(root.node)))
            .WillByDefault(Return(Result{Status::Running, &try_catch}));
        engine.step();
    }

    void step_to_try_catch()
    {
        ON_CALL(root.actions, loop(ContextNodeEquals(root.node)))
            .WillByDefault(Return(Result{Status::Running, &try_catch}));
        engine.step();
    }
    void step_to_try_branch()
    {
        step_to_try_catch();

        EXPECT_CALL(mock_try.actions, loop(ContextNodeEquals(mock_try.node)))
            .WillOnce(Return(Result{Status::Running}));
        engine.step();
    }
    void step_to_catch_branch()
    {
        step_to_try_branch();

        EXPECT_CALL(mock_try.actions, on_exception(ExceptionEquals(expected_ex), _)).Times(1);
        engine.on_exception(expected_ex);
        engine.step();

        EXPECT_CALL(mock_catch.actions, loop(ContextNodeEquals(mock_catch.node)))
            .WillOnce(Return(Result{Status::Running}));
        engine.step();
    }
};

TEST_F(EngineExceptionsTest, unhandled_exception)
{
    Scenario << "An exception is raised that is not handled in the tree"
             << "The engine recovers gracefully by re-entering the root node";
    Given << "an engine traversing the tree"
          << "the tree does not have have exception handling";

    MockNode<0> tree;
    MockNode<1> branch;
    engine.configure(&tree.node, stack, stack_len);

    EXPECT_CALL(tree.actions, loop(ContextNodeEquals(tree.node)))
        .WillOnce(Return(Result{Status::Running, &branch.node}));
    engine.step();

    // return success/fail to return to parent node
    EXPECT_CALL(branch.actions, loop(ContextNodeEquals(branch.node)))
        .WillOnce(Return(Result{Status::Running}));
    engine.step();

    When << "an exception is raised in the tree";
    EXPECT_CALL(branch.actions, on_exception(ExceptionEquals(expected_ex), _)).Times(1);
    EXPECT_CALL(tree.actions, on_exception(ExceptionEquals(expected_ex), _)).Times(1);
    engine.on_exception(expected_ex);

    EXPECT_CALL(tree.actions, loop(ContextNodeEquals(tree.node)))
        .WillOnce(Return(Result{Status::Running, &branch.node}));
    engine.step();
    Then << "the engine pops the tree and traverses to the root node";
}

TEST_F(EngineExceptionsTest, exception_is_caught)
{
    Scenario << "An exception is raised and is caught";

    // ---
    Given << "a tree containing a try catch node with 1 try branch and 1 catch "
             "branch";
    Given << "the engine looping on the try branch";
    step_to_try_branch();

    // ---
    When << "an exception is raised in the tree";
    When << "the engine steps";
    Then << "the engine traverses to the catch node";
    EXPECT_CALL(mock_try.actions, on_exception(ExceptionEquals(expected_ex), _)).Times(1);
    EXPECT_CALL(mock_catch.actions, setup(_)).Times(1);
    engine.on_exception(expected_ex);
    engine.step();
}

TEST_F(EngineExceptionsTest, unhandled_exception_during_catch)
{
    Scenario << "An exception raised in a catch node becomes an unhandled "
                "exception.";

    Given << "a tree containing a try catch node with 1 try branch and 1 catch "
             "branch";
    Given << "the engine looping on the catch branch";
    step_to_catch_branch();

    When << "an exception is raised";
    When << "the engine steps";
    Then << "the engine traverses to the root node";
    Then << "the engine loops on the root node";
    EXPECT_CALL(mock_catch.actions, on_exception(ExceptionEquals(expected_ex), _)).Times(1);
    EXPECT_CALL(root.actions, on_exception(ExceptionEquals(expected_ex), _)).Times(1);
    EXPECT_CALL(root.actions, loop(ContextNodeEquals(root.node)))
        .WillOnce(Return(Result{Status::Success}));
    engine.on_exception(expected_ex);
    engine.step();
}

TEST_F(EngineExceptionsTest, current_exception_available_in_catch_branch)
{
    Scenario << "The catch branch needs the current exception in order to make "
                "a decision";

    Given << "a try-catch tree active on the catch branch";
    step_to_catch_branch();

    When << "looping on the node";
    Then << "the current exception in the context does exist";
    EXPECT_CALL(mock_catch.actions, loop(ContextExceptionEquals(expected_ex)))
        .WillOnce(Return(Result{Status::Running}));
    engine.step();
}

TEST_F(EngineExceptionsTest, current_exception_not_available_in_try_branch)
{
    Scenario << "The current exception does not exist in a try branch";

    Given << "a try-catch tree active on the try branch";
    step_to_try_branch();

    When << "looping on the node";
    Then << "the current exception in the context does not exist";
    EXPECT_CALL(mock_try.actions, loop(DoNotExpectContextException()))
        .WillOnce(Return(Result{Status::Running}));
    engine.step();
}

TEST_F(EngineExceptionsTest, current_exception_retires_after_successful_handling)
{
    Scenario << "The catch branch successfully handles the exception";

    Given << "a try-catch tree active on the catch branch";
    step_to_catch_branch();

    When << "a catch branch is successful";
    EXPECT_CALL(mock_catch.actions, loop(ContextExceptionEquals(expected_ex)))
        .WillOnce(Return(Result{Status::Success}));
    engine.step();
    engine.step();  // step through try catch node

    Then << "the current exception is retired";
    EXPECT_CALL(root.actions, loop(DoNotExpectContextException()))
        .WillOnce(Return(Result{Status::Success}));
    engine.step();
}

TEST_F(EngineExceptionsTest, current_exception_rethrown_after_failed_handling)
{
    Given << "a try-catch tree active on the catch branch";
    step_to_catch_branch();

    When << "a catch branch fails";
    EXPECT_CALL(mock_catch.actions, loop(ContextExceptionEquals(expected_ex)))
        .WillOnce(Return(Result{Status::Fail}));
    engine.step();

    Then << "the exception is rethrown";
    EXPECT_CALL(root.actions, on_exception(ExceptionEquals(expected_ex), _));
    engine.step();
}
