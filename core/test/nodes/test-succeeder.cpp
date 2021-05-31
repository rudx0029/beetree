#include "beetree/nodes/succeeder.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/fakes/test-node.hpp"

using namespace bte;
using gtest::Eq;

class SucceederTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("btree-lite"); }
    void        SetUp() override { test.setup(); }
    void        TearDown() override { test.teardown(); }

    Node           branch{nullptr};
    test::TestNode test{make_succeeder, branch};
};

TEST_F(SucceederTests, first_time)
{
    Scenario << "an succeeder decorator returns its branch on its first loop";

    Given << "an succeeder node with a branch";
    When << "looping on the node for the first time";
    auto result = test->loop(test.context());

    Then << "the branch and a running status is the result";
    EXPECT_THAT(result.branch, Eq(&branch));
    EXPECT_THAT(result.status, Eq(Status::Running));
}

TEST_F(SucceederTests, branch_successful_succeeder_successful)
{
    Scenario << "an succeeder decorator fails when its branch succeeds";

    Given << "an succeeder decorator with its branch active";
    test->loop(test.context());

    When << "the branch completes successfully";
    test->on_branch_complete(Status::Success, test.context());

    Then << "the succeeder indicates success";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Success));
}

TEST_F(SucceederTests, branch_failed_succeeder_successful)
{
    Scenario << "an succeeder decorator succeeds when its branch fails";

    Given << "an succeeder decorator with its branch active";
    test->loop(test.context());

    When << "the branch completes as failed";
    test->on_branch_complete(Status::Fail, test.context());

    Then << "the succeeder indicates success";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Success));
}