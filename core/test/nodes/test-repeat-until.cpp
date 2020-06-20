//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include <array>
#include <memory>

#include "beetree/engine/context.hpp"
#include "beetree/engine/recipe.hpp"
#include "beetree/nodes/repeat-until.hpp"
#include "beetree/test/behavior-reqs.hpp"
#include "beetree/test/fakes/test-node.hpp"

using namespace bte;
using gtest::Eq;

class RepeatUntilTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("btree-lite"); }

    RepeatUntilTests() : branch(nullptr), test(make_repeat_until_success, branch) {}
    RepeatUntilTests(delegate::Build fnc) : branch(nullptr), test(fnc, branch) {}

    void SetUp() override { test.setup(); }
    void TearDown() override { test.teardown(); }

    Node           branch;
    test::TestNode test;
};

class RepeatUntilSuccessTests : public RepeatUntilTests
{
protected:
    RepeatUntilSuccessTests() : RepeatUntilTests(make_repeat_until_success) {}
};

class RepeatUntilFailTests : public RepeatUntilTests
{
protected:
    RepeatUntilFailTests() : RepeatUntilTests(make_repeat_until_fail) {}
};

TEST_F(RepeatUntilTests, first_time)
{
    Scenario << "a repeat until decorator returns its branch on its first loop";
    Given << "a repeat until node with a branch";
    When << "looping on the node for the first time";
    auto result = test->loop(test.context());

    Then << "the branch and a running status is the result";
    EXPECT_THAT(result.status, Eq(Status::Running));
    EXPECT_THAT(result.branch, Eq(&branch));
}

TEST_F(RepeatUntilSuccessTests, repeat_branch_when_not_successful)
{
    Scenario << "Repeat Until Success Decorator continues to run its branch "
                "when the branch has failed (not successful)";
    Given << "a Repeat Until Success node";
    auto setup = test->loop(test.context());

    When << "its branch completes with a failed status";
    test->on_branch_complete(Status::Fail, test.context());

    Then << "continue to loop the branch";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Running));
    EXPECT_THAT(result.branch, Eq(&branch));
}

TEST_F(RepeatUntilFailTests, repeat_branch_when_not_failed)
{
    Scenario << "Repeat Until Fail Decorator continues to run its branch "
                "when the branch succeeded (not failed)";
    Given << "a Repeat Until Fail node";
    auto setup = test->loop(test.context());

    When << "its branch completes with a success status";
    test->on_branch_complete(Status::Success, test.context());

    Then << "continue to loop the branch";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Running));
    EXPECT_THAT(result.branch, Eq(&branch));
}

TEST_F(RepeatUntilSuccessTests, stop_when_branch_is_successful)
{
    Scenario << "Repeat Until Success Decorator stops repeating the branch "
                "when the branch is successful";
    Given << "a Repeat Until Success node";
    auto setup = test->loop(test.context());

    When << "its branch completes with a success status";
    test->on_branch_complete(Status::Success, test.context());

    Then << "the repeat until success node stops repeating the branch and "
            "returns a success result";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Success));
}

TEST_F(RepeatUntilFailTests, stop_when_branch_has_failed)
{
    Scenario << "Repeat Until Fail Decorator stops repeating the branch "
                "when the branch has failed";
    Given << "a Repeat Until Fail node";
    auto setup = test->loop(test.context());

    When << "its branch completes with a failed status";
    test->on_branch_complete(Status::Fail, test.context());

    Then << "the repeat until fail node stops repeating the branch and "
            "returns a failed result";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Fail));
}