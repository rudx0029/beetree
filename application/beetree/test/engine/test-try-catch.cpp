
#include "beetree/engine/try-catch.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/fakes/test-node.hpp"
#include "beetree/test-api/gtest-ns.hpp"

using namespace bte;
using gtest::Eq;

class TryCatchTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("beetree"); }
    void        SetUp() override { test.setup(); }
    void        TearDown() override { test.teardown(); }

    Node             try_branch   = bte::Leaf<test::TestNode::no_op>();
    Node             catch_branch = bte::Leaf<test::TestNode::no_op>();
    bte::Branches<2> branches     = bte::branches(try_branch, catch_branch);
    test::TestNode   test{try_catch_all, branches};
};

TEST_F(TryCatchTests, first_time)
{
    Scenario << "a try catch node returns the try branch on its first loop";

    Given << "a trycatch node";
    When << "looping on the node for the first time";
    auto result = test->loop(test.context());

    Then << "the try branch is returned";
    EXPECT_THAT(result.branch, Eq(&try_branch));

    Then << "the node is running";
    EXPECT_THAT(result.status, Eq(Status::Running));
}

TEST_F(TryCatchTests, exception_occurs)
{
    Scenario << "a try catch node returns catch branch on an exception";

    Given << "a trycatch node";
    test->loop(test.context());

    When << "an exception occurs";
    test->on_exception(Exception{ExceptionType::ALL}, test.context());

    Then << "the catch branch is returned";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.branch, Eq(&catch_branch));

    Then << "the node is running";
    EXPECT_THAT(result.status, Eq(Status::Running));
}

TEST_F(TryCatchTests, try_branch_succeeds)
{
    Scenario << "a try catch node succeeds when the try branch succeeds";

    Given << "a trycatch node";
    test->loop(test.context());

    When << "the try branch succeeds";
    test->on_branch_complete(Status::Success, test.context());

    Then << "the node is successful";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Success));
}

TEST_F(TryCatchTests, try_branch_fails)
{
    Scenario << "a try catch node fails when the try branch fails";

    Given << "a trycatch node";
    test->loop(test.context());

    When << "the try branch fails";
    test->on_branch_complete(Status::Fail, test.context());

    Then << "the node fails";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Fail));
}

TEST_F(TryCatchTests, catch_branch_succeeds)
{
    Scenario << "a try catch node succeeds when the catch branch succeeds";

    Given << "a trycatch node";
    test->loop(test.context());
    test->on_exception(Exception{ExceptionType::ALL}, test.context());
    test->loop(test.context());

    When << "the catch branch succeeds";
    test->on_branch_complete(Status::Success, test.context());

    Then << "the node succeeds";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Success));
}

TEST_F(TryCatchTests, catch_branch_fails)
{
    Scenario << "a try catch node fails when the catch branch fails";

    Given << "a trycatch node";
    test->loop(test.context());
    test->on_exception(Exception{ExceptionType::ALL}, test.context());
    test->loop(test.context());

    When << "the catch branch succeeds";
    test->on_branch_complete(Status::Fail, test.context());

    Then << "the node succeeds";
    auto result = test->loop(test.context());
    EXPECT_THAT(result.status, Eq(Status::Fail));
}