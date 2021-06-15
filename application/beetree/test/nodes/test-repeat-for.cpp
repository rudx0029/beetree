//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include <array>

#include "beetree/nodes/repeat-for.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/fakes/test-node.hpp"

using namespace bte;
using gtest::Eq;

class RepeatForTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("btree-lite"); }
    void        SetUp() override
    {
        for (auto test : tests) test.second->setup();
    }
    void TearDown() override
    {
        for (auto test : tests) test.second->teardown();
    }

    Node           branch{nullptr};
    test::TestNode test1{make_repeat_for<1>, branch};
    test::TestNode test2{make_repeat_for<2>, branch};
    test::TestNode test3{make_repeat_for<3>, branch};
    test::TestNode test5{make_repeat_for<5>, branch};
    test::TestNode test8{make_repeat_for<8>, branch};
    test::TestNode testN{make_repeat_for<13>, branch};

    std::map<std::size_t, test::TestNode*> tests{{1, &test1},
                                                 {2, &test2},
                                                 {3, &test3},
                                                 {5, &test5},
                                                 {8, &test8},
                                                 {13, &testN}};
};

TEST_F(RepeatForTests, first_time)
{
    Scenario << "a RepeatFor<N> decorator node returns its branch on its first loop";

    Given << "a RepeatFor<N> node with a branch";
    When << "looping on the node for the first time";
    Then << "the branch and a running status is the result";

    for (auto test : tests)
    {
        // Given
        // When
        test::TestNode& node   = *test.second;
        auto            result = node->loop(node.context());

        // Then
        EXPECT_THAT(result.status, Eq(Status::Running));
        EXPECT_THAT(result.branch, Eq(&branch));
    }
}

TEST_F(RepeatForTests, branch_indicates_failure)
{
    Scenario << "A RepeatFor<N> decorator node indicates failed when its "
                "branch indicates failed";

    Given << "a RepeatFor<N> node with successful branch completions";
    testN->loop(testN.context());  // ignore the result
    testN->on_branch_complete(Status::Success, testN.context());
    testN->loop(testN.context());

    When << "the branch fails";
    testN->on_branch_complete(Status::Fail, testN.context());

    Then << "the RepeatFor<N> node indicates failure";
    auto result = testN->loop(testN.context());
    EXPECT_THAT(result.status, Eq(Status::Fail));
}

TEST_F(RepeatForTests, branch_repeats_successfully)
{
    Scenario << "The RepeatFor<N> Decorator indicates success when the branch "
                "has looped N times successfully.";

    Given << "a RepeatFor<N> node with N successful branch completions";
    When << "the node loops for the N+1 time";
    Then << "the node indicates a successful result";

    for (auto test : tests)
    {
        test::TestNode& node = *test.second;
        for (std::size_t i = 0; i < test.first; i++)
        {
            auto result = node->loop(node.context());
            EXPECT_THAT(result.status, Eq(Status::Running));

            node->on_branch_complete(Status::Success, node.context());
        }
        auto result = node->loop(node.context());
        EXPECT_THAT(result.status, Eq(Status::Success));
    }
}