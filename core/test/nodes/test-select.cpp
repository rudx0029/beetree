#include "beetree/nodes/select.hpp"
#include "beetree/test/behavior-reqs.hpp"
#include "beetree/test/fakes/test-node.hpp"

using namespace bte;
using gtest::Eq;

class SelectTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("beetree-lite"); }
    void        SetUp() override { test.setup(); }
    void        TearDown() override { test.teardown(); }

    Node           branch_1 = Leaf<test::TestNode::no_op>();
    Node           branch_2 = Leaf<test::TestNode::no_op>();
    Node           branch_3 = Leaf<test::TestNode::no_op>();
    Branches<3>    branches = bte::branches(branch_1, branch_2, branch_3);
    test::TestNode test{make_select, branches};
};

TEST_F(SelectTests, first_time)
{
    Scenario << "a sequence composite returns its branch on its first loop";

    Given << "a select node with at least 1 branch";
    When << "looping on the node for the first time";
    auto result = test->loop(test.context());

    Then << "the first branch is returned";
    EXPECT_THAT(result.branch, Eq(&branch_1));

    Then << "the node is running";
    EXPECT_THAT(result.status, Eq(Status::Running));
}

TEST_F(SelectTests, branch_fails)
{
    Scenario << "When a branch fails, the select node returns the next branch";

    Given << "A select node with more than one branches";
    test->loop(test.context());

    When << "the branch failes";
    test->on_branch_complete(Status::Fail, test.context());

    Then << "the node returns the next branch";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.branch, Eq(&branch_2));

    Then << "the node is running";
    EXPECT_THAT(result.status, Eq(Status::Running));
}

TEST_F(SelectTests, branch_succeeds)
{
    Scenario << "When a branch succeeds, the select node succeeds";

    Given << "A select node with more than one branches";
    test->loop(test.context());
    test->on_branch_complete(Status::Fail, test.context());
    test->loop(test.context());

    When << "a branch succeeds";
    test->on_branch_complete(Status::Success, test.context());

    Then << "the node succeeds";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Success));
}

TEST_F(SelectTests, all_fail)
{
    Scenario << "When all branches fail, then select node fail";

    Given << "A select node with more than 1 branches";
    When << "all the branches fail";
    test->loop(test.context());
    test->on_branch_complete(Status::Fail, test.context());
    test->loop(test.context());
    test->on_branch_complete(Status::Fail, test.context());
    test->loop(test.context());
    test->on_branch_complete(Status::Fail, test.context());

    Then << "the node fails";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Fail));
}