#include "beetree/nodes/sequence.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/fakes/test-node.hpp"

using namespace bte;
using gtest::Eq;

class SequenceTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("beetree-lite"); }
    void        SetUp() override { test.setup(); }
    void        TearDown() override { test.teardown(); }

    Node           branch_1 = Leaf<test::TestNode::no_op>();
    Node           branch_2 = Leaf<test::TestNode::no_op>();
    Node           branch_3 = Leaf<test::TestNode::no_op>();
    Branches<3>    branches = bte::branches(branch_1, branch_2, branch_3);
    test::TestNode test{make_sequence, branches};
};

TEST_F(SequenceTests, first_time)
{
    Scenario << "a sequence composite returns its branch on its first loop";

    Given << "a sequence node with at least 1 branch";
    When << "looping on the node for the first time";
    auto result = test->loop(test.context());

    Then << "the first branch is returned";
    EXPECT_THAT(result.branch, Eq(&branch_1));
    Then << "the node is running";
    EXPECT_THAT(result.status, Eq(Status::Running));
}

TEST_F(SequenceTests, branch_succeeds)
{
    Scenario << "When a sequence node's branch succeeds, then the node returns "
                "the next branch";

    Given << "a sequence node with more than 1 branch";
    test->loop(test.context());
    When << "a sequence node's branch succeeds";
    test->on_branch_complete(Status::Success, test.context());

    Then << "the next branch is returned";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.branch, Eq(&branch_2));
    Then << "the node is still running";
    EXPECT_THAT(result.status, Eq(Status::Running));
}

TEST_F(SequenceTests, branch_fails)
{
    Scenario << "When a sequence node's branch fails, then the sequence node fails";

    Given << "a squence node with more than 1 branch";
    test->loop(test.context());
    test->on_branch_complete(Status::Success, test.context());
    test->loop(test.context());

    When << "a branch fails";
    test->on_branch_complete(Status::Fail, test.context());

    Then << "the node fails";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Fail));
}

TEST_F(SequenceTests, all_succeed)
{
    Scenario << "When all branches succeed, then sequence node succeeds";

    Given << "A sequence node with more than 1 branches";
    When << "all the branches succeed";
    test->loop(test.context());
    test->on_branch_complete(Status::Success, test.context());
    test->loop(test.context());
    test->on_branch_complete(Status::Success, test.context());
    test->loop(test.context());
    test->on_branch_complete(Status::Success, test.context());

    Then << "the node succeeds";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Success));
}