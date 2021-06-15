//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/nodes/inverter.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/fakes/test-node.hpp"

using namespace bte;
using gtest::Eq;

class InverterTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("btree-lite"); }
    void        SetUp() override { test.setup(); }
    void        TearDown() override { test.teardown(); }

    Node           branch{nullptr};
    test::TestNode test{bte::make_inverter, branch};
};

TEST_F(InverterTests, first_time)
{
    Scenario << "an inverter decorator returns its branch on its first loop";

    Given << "an inverter node with a branch";
    When << "looping on the node for the first time";
    auto result = test->loop(test.context());

    Then << "the branch and a running status is the result";
    EXPECT_THAT(result.branch, Eq(&branch));
    EXPECT_THAT(result.status, Eq(Status::Running));
}

TEST_F(InverterTests, branch_successful_inverter_failed)
{
    Scenario << "an inverter decorator fails when its branch succeeds";

    Given << "an inverter decorator with its branch active";
    test->loop(test.context());

    When << "the branch completes successfully";
    test->on_branch_complete(Status::Success, test.context());

    Then << "the inverter indicates failure";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Fail));
}

TEST_F(InverterTests, branch_failed_inverter_successful)
{
    Scenario << "an inverter decorator succeeds when its branch fails";

    Given << "an inverter decorator with its branch active";
    test->loop(test.context());

    When << "the branch completes as failed";
    test->on_branch_complete(Status::Fail, test.context());

    Then << "the inverter indicates success";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Success));
}