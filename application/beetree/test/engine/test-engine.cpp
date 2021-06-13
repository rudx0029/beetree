#include <array>
#include "beetree/engine/builder.hpp"
#include "beetree/engine/engine.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/test-api/matchers/node.hpp"
#include "beetree/test-api/mocks/mock-node.hpp"
#include "beetree/test-api/mocks/platform-mock.hpp"

using namespace bte;
using namespace bte::test;

using gtest::_;
using gtest::Return;

/// Test Fixture for btree_lite::Engine tests
class EngineTest : public BehaviorReqTest
{
protected:
    // ------------------------------------------------------
    // Properties and Mocks
    // ------------------------------------------------------
    PlatformMock platform;  // for mocking time, just need to declare it

    // Engine Stack Configuration
    static constexpr std::size_t stack_len = 256;
    uint8_t                      stack[stack_len];

    // Mock Nodes
    MockNode<0> tree;      // mock node for the base of the tree
    MockNode<1> branch_a;  // mocks a branch on the tree
    MockNode<2> branch_b;  // moacks another branch of the tree

    // The Engine
    Engine engine;

    // ------------------------------------------------------
    // Methods
    // ------------------------------------------------------

    static void SetUpTestCase() { BehaviorReqTest::Feature("beetree"); }

    void SetUp() override { reset_engine(); }

    void reset_engine() { engine.configure(&tree.node, stack, stack_len); }
};

TEST_F(EngineTest, loops_on_root_node_for_first_time)
{
    Scenario << "The engine loops on to the root node for the first time";
    Given << "an engine with a root node";
    When << "the engine is stepped for the first time";
    Then << "the root node is executed once";

    EXPECT_CALL(tree.actions, setup(_)).Times(1);
    EXPECT_CALL(tree.actions, loop(_)).WillOnce(Return(Status::Success));

    engine.step();
}

TEST_F(EngineTest, loop_on_running_leaf)
{
    Scenario << "The engine continually loops on a running leaf";
    Given << "an engine traversing a tree"
          << "the current node has a status of Running"
          << "the current node does not have a branch";

    EXPECT_CALL(tree.actions, loop(_)).WillOnce(Return(Result{Status::Running, nullptr}));

    When << "the engine makes a step";
    EngineResult r = engine.step();

    Then << "the engine returns a running status"
         << "the current node (a leaf node) is still running";
    EXPECT_EQ(r.node_status, Status::Running);
    EXPECT_TRUE(r.is_running_leaf);
}

TEST_F(EngineTest, transitions_to_branch_after_step)
{
    Scenario << "The engine transitions from a decorator or composite node to "
                "a branch after a step";

    Given << "an engine traversing a tree"
          << "the current node has a branch"
          << "the current node has a Running Status";

    EXPECT_CALL(tree.actions, loop(ContextNodeEquals(tree.node)))
        .WillOnce(Return(Result{Status::Running, &branch_a.node}));

    When << "the engine makes a step";
    engine.step();

    Then << "the branch becomes the current node";
    EXPECT_CALL(branch_a.actions, loop(ContextNodeEquals(branch_a.node)))
        .WillOnce(Return(Result{Status::Running, nullptr}));

    Then << "the engine returns a running status";
    EngineResult r = engine.step();
    EXPECT_EQ(r.node_status, Status::Running);
}

TEST_F(EngineTest, return_from_branch_after_step)
{
    Scenario << "After a branch completes, the engine returns to parent node";
    Given << "an engine traversing a tree"
          << "the current node is a branch"
          << "the current node has a status of Success or Fail";
    When << "the engine makes a step";
    Then << "the active node becomes the parent of the branch"
         << "the engine returns a Running status";

    auto test_cases = {Status::Success, Status::Fail};
    for (Status success_fail : test_cases)
    {
        reset_engine();

        // GIVEN...
        // sets branch_a as active node.
        EXPECT_CALL(tree.actions, loop(ContextNodeEquals(tree.node)))
            .WillOnce(Return(Result{Status::Running, &branch_a.node}))
            .RetiresOnSaturation();
        engine.step();

        // return success/fail to return to parent node
        EXPECT_CALL(branch_a.actions, loop(ContextNodeEquals(branch_a.node)))
            .WillOnce(Return(Result{success_fail}))
            .RetiresOnSaturation();

        // WHEN...
        engine.step();

        // THEN...
        EXPECT_CALL(tree.actions, loop(ContextNodeEquals(tree.node)))
            .WillOnce(Return(Result{Status::Running}))
            .RetiresOnSaturation();
        EngineResult result = engine.step();
        EXPECT_EQ(result.node_status, Status::Running);
    }
}

TEST_F(EngineTest, loops_on_root_node_for_last_time)
{
    Scenario << "";
    Given << "an engine traversing a tree"
          << "the current node is the base/root node"
          << "the current node's status is Success/Fail";
    When << "then engine makes a step";
    Then << "the engine returns a status of Success/Fail";

    auto test_cases = {Status::Success, Status::Fail};
    for (Status success_fail : test_cases)
    {
        reset_engine();

        // GIVEN...
        EXPECT_CALL(tree.actions, loop(ContextNodeEquals(tree.node)))
            .WillOnce(Return(Result{success_fail}))
            .RetiresOnSaturation();

        // WHEN ....
        EngineResult r = engine.step();

        // THEN ...
        EXPECT_EQ(r.node_status, success_fail);
    }
}
