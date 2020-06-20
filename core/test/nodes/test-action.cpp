#include "beetree/nodes/action.hpp"
#include "beetree/test/behavior-reqs.hpp"
#include "beetree/test/fakes/test-node.hpp"
#include "beetree/test/gtest-ns.hpp"

using namespace bte;

class ActionLeafTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("btree-lite"); }

    void SetUp() override
    {
        delegate_invoked = false;
        invalid_action.setup();
        valid_action.setup();
    }

    static bool delegate_invoked;
    static void delegate() { delegate_invoked = true; }

    static constexpr TraceToken token{};
    test::TestNode              invalid_action{bte::make_action<nullptr, token>};
    test::TestNode              valid_action{bte::make_action<delegate, token>};
};
constexpr TraceToken ActionLeafTests::token;
bool                 ActionLeafTests::delegate_invoked = false;

TEST_F(ActionLeafTests, null_action)
{
    Scenario << "An action leaf ignores an invalid delegate and reports successful";

    Given << "an action leaf with an invalid delegate";
    When << "invoked";
    Result result = invalid_action->loop(invalid_action.context());

    Then << "the action is successful and the invalid delegate is not invoked "
            "(seg fault, otherwise)";
    EXPECT_TRUE(result.status == Status::Success);
}

TEST_F(ActionLeafTests, whenActionIsInvoked_thenStatusIsSuccess)
{
    Scenario << "An action leaf invokes it's delegate and reports success.";

    Given << "an action leaf with a valid delegate";
    When << "invoked";
    Result result = valid_action->loop(valid_action.context());

    Then << "the delegate is invoked";
    EXPECT_TRUE(delegate_invoked);
    Then << "the action is successful";
    EXPECT_TRUE(result.status == Status::Success);
}