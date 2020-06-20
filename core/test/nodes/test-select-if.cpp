#include "beetree/nodes/select-if.hpp"
#include "beetree/test/behavior-reqs.hpp"
#include "beetree/test/fakes/test-node.hpp"

using namespace bte;
using gtest::Eq;

class SelectIfTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("btree-lite"); }
    void        SetUp() override
    {
        test_true.setup();
        test_false.setup();
        test_null.setup();
    }
    void TearDown() override
    {
        test_true.teardown();
        test_false.teardown();
        test_null.teardown();
    }

    static bool predicate_returns_true() { return true; }
    static bool predicate_returns_false() { return false; }

    Node           branch{nullptr};
    test::TestNode test_true{make_select_if<predicate_returns_true>, branch};
    test::TestNode test_false{make_select_if<predicate_returns_false>, branch};
    test::TestNode test_null{make_select_if<nullptr>, branch};
};

TEST_F(SelectIfTests, null_predicate)
{
    Scenario << "Do not select the branch if there is no decision (predicate)";
    Given << "a select-if node";
    When << "the predicate is invalid";
    Result result = test_null->loop(test_null.context());

    Then << "the node fails";
    EXPECT_THAT(result.status, Eq(Status::Fail));
}

TEST_F(SelectIfTests, false_predicate)
{
    Scenario << "Do not select the branch if the decision is no (predicate is "
                "false)";
    Given << "a select-if node";
    When << "the predicate is false";
    Result result = test_false->loop(test_false.context());

    Then << "the node fails";
    EXPECT_THAT(result.status, Eq(Status::Fail));
}

TEST_F(SelectIfTests, true_predicate)
{
    Scenario << "Select the branch if the decision is yes (predicate is true)";

    Given << "a select-if node";
    When << "the predicate is true";
    Result result = test_true->loop(test_true.context());

    Then << "the node is running";
    EXPECT_THAT(result.status, Eq(Status::Running));
    Then << "its branch is returned";
    EXPECT_THAT(result.branch, Eq(&branch));
}

TEST_F(SelectIfTests, branch_succeeds)
{
    Scenario << "The select-if decorator succeeds when the branch succeeds";

    Given << "a select-if node";
    Given << "the predicate is true";
    test_true->loop(test_true.context());

    When << "the branch succeeds";
    test_true->on_branch_complete(Status::Success, test_true.context());

    Then << "the node succeeds";
    Result result = test_true->loop(test_true.context());
    EXPECT_THAT(result.status, Eq(Status::Success));
}

TEST_F(SelectIfTests, branch_fails)
{
    Scenario << "The select-if decorator fails when the branch fails";

    Given << "a select-if node";
    Given << "the predicate is true";
    test_true->loop(test_true.context());

    When << "the branch fails";
    test_true->on_branch_complete(Status::Fail, test_true.context());

    Then << "the node fails";
    Result result = test_true->loop(test_true.context());
    EXPECT_THAT(result.status, Eq(Status::Fail));
}