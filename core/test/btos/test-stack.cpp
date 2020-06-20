//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/btos/stack.hpp"
#include "beetree/test/behavior-reqs.hpp"
#include "beetree/test/gtest-ns.hpp"

using namespace bte;

class StackTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("beetree-btos"); }

    static constexpr std::size_t N = 5;
    bte::StackContainer<int, N>  stack;
};
const std::size_t StackTests::N;

TEST_F(StackTests, stack_is_empty)
{
    EXPECT_TRUE(stack->empty());
    EXPECT_FALSE(stack->full());
}

TEST_F(StackTests, not_empty_and_not_full)
{
    stack->push(0);
    EXPECT_FALSE(stack->empty());
    EXPECT_FALSE(stack->full());
}

TEST_F(StackTests, push_and_stack_is_full)
{
    int i    = 0;
    int item = N;

    while (!stack->full())
    {
        stack->push(item);
        EXPECT_EQ(item, stack->top());

        item--;
        i++;
    }

    EXPECT_TRUE(stack->full());
    EXPECT_EQ(i, N);
}

TEST_F(StackTests, pop_and_stack_is_empty)
{
    int item = N;
    int i    = 0;

    while (!stack->full())
    {
        stack->push(item--);
    }

    while (!stack->empty())
    {
        EXPECT_EQ(stack->top(), ++item);
        stack->pop();
        i++;
    }

    EXPECT_TRUE(stack->empty());
    EXPECT_EQ(i, N);
}

TEST_F(StackTests, clear_stack)
{
    while (!stack->full())
    {
        stack->push(0);
    }

    stack->clear();

    EXPECT_TRUE(stack->empty());
}