///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#include "beetree/engine/node.hpp"
#include "beetree/engine/recipe.hpp"
#include "beetree/engine/stack.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/gtest-ns.hpp"

#include <array>
#include <ios>

using namespace bte;

class StackTest : public test::BehaviorReqTest
{
protected:
    // ------------------------------------------------------
    // Properties and Mocks
    // ------------------------------------------------------

    // > Stack Configuration
    static constexpr std::size_t buff_len = 256;
    uint8_t                      buffer[buff_len];

    // > The Stack under Test
    Stack stack;

    // ------------------------------------------------------
    // Methods
    // ------------------------------------------------------

    // > Test Fixture
    static void SetUpTestCase() { Feature("beetree"); }
    void        SetUp() override { stack.configure(buffer, buff_len); }

    // > Mocks
    static Recipe build_fnc() { return Recipe(); }
    static Recipe build_fnc2() { return Recipe(); }
};

TEST_F(StackTest, push_node_on_empty_stack)
{
    Given << "an empty stack";
    EXPECT_TRUE(stack.empty());
    EXPECT_FALSE(stack.top().is_valid());

    When << "pushing a node";
    Node n(build_fnc);
    bool is_pushed = stack.push(n, 0);  // push with no data
    ASSERT_TRUE(is_pushed);             // ensures we have enough mem allocated

    Then << "the stack is not empty";
    EXPECT_FALSE(stack.empty());
    EXPECT_TRUE(stack.top().is_valid());
}

TEST_F(StackTest, push_node)
{
    Given << "a stack with one or more nodes";
    Node n(build_fnc);
    for (int i = 0; i < 3; i++)
    {
        stack.push(n, 0);
    }

    When << "pushing a node";
    Node expected(build_fnc2);
    bool is_pushed = stack.push(expected, 0);
    ASSERT_TRUE(is_pushed);  // ensures we have enough mem allocated

    Then << "the new node is placed on the top of the stack";
    ASSERT_TRUE(stack.top().is_valid());
    EXPECT_TRUE(stack.top().node->build == expected.build);
}

TEST_F(StackTest, pop_node)
{
    Scenario << "popping the top of the stack containing more than 1 node";

    Given << "a stack with multiple nodes";
    Node n1(build_fnc);
    ASSERT_TRUE(stack.push(n1, 0));
    Node n2(build_fnc2);
    ASSERT_TRUE(stack.push(n2, 0));

    When << "popping the top node";
    stack.pop();

    Then << "the previous node is at the top of the stack";
    ASSERT_TRUE(stack.top().is_valid());
    EXPECT_TRUE(stack.top().node->build == n1.build);
}

TEST_F(StackTest, pop_last_node)
{
    Scenario << "popping the last node results in an empty stack";

    Given << "a stack with 1 node";
    Node n1(build_fnc);
    ASSERT_TRUE(stack.push(n1, 0));

    When << "popping the last node";
    stack.pop();

    Then << "the stack is empty";
    EXPECT_TRUE(stack.empty());
}

TEST_F(StackTest, out_of_memory)
{
    Scenario << "pushing a node on the stack fails when it is out of memory";

    Given << "a stack";
    When << "pushing nodes, continuously";

    bool is_out_of_memory = false;
    int  i                = 0;
    Node n(build_fnc);
    for (i = 0; i < 100 && !is_out_of_memory; i++)
    {
        is_out_of_memory = !stack.push(n, 0);
    }

    Then << "the stack is out of memory";
    EXPECT_TRUE(is_out_of_memory);
    EXPECT_GT(i, 2);  // to show that the test ran
}
