//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/engine/connections.hpp"
#include "beetree/engine/engine.hpp"
#include "beetree/engine/port.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/test-api/matchers/node.hpp"
#include "beetree/test-api/mocks/mock-node.hpp"
#include "beetree/test-api/mocks/platform-mock.hpp"

using namespace bte;
using namespace bte::test;

using gtest::_;
using gtest::Return;

class PortTests : public BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("beetree"); }

    // > Mock Try Catch Tree
    PlatformMock      platform;  // for mocking time
    MockNode<0, true> root;
    MockNode<1, true> mock_connection_m;
    MockNode<2, true> mock_connection_o;
    MockNode<3, true> mock_noise;

    PortMandatory port_m;
    PortMandatory port_m_noise1;
    PortMandatory port_m_noise2;
    PortOptional  port_o;
    PortOptional  port_o_noise1;
    PortOptional  port_o_noise2;

    ConnectionArray<6> all_connections =
        pin_connections(Connection{port_m_noise1, mock_noise.node},
                        Connection{port_m, mock_connection_m.node},
                        Connection{port_m_noise2, mock_noise.node},
                        Connection{port_o, mock_connection_o.node},
                        Connection{port_o_noise1, mock_noise.node},
                        Connection{port_o_noise2, mock_noise.node});

    ConnectionArray<5> no_m_connection =
        pin_connections(Connection{port_m_noise1, mock_noise.node},
                        Connection{port_m_noise2, mock_noise.node},
                        Connection{port_o, mock_connection_o.node},
                        Connection{port_o_noise1, mock_noise.node},
                        Connection{port_o_noise2, mock_noise.node});

    ConnectionArray<5> no_o_connection =
        pin_connections(Connection{port_m_noise1, mock_noise.node},
                        Connection{port_m, mock_connection_m.node},
                        Connection{port_m_noise2, mock_noise.node},
                        Connection{port_o_noise1, mock_noise.node},
                        Connection{port_o_noise2, mock_noise.node});

    // > Engine
    Engine                       engine;
    static constexpr std::size_t stack_len = 256;
    uint8_t                      stack[stack_len];

    void setup(const Connections& connections_under_test, const Node& node_under_test)
    {
        engine.configure(&root.node, stack, stack_len);
        engine.configure_connections(connections_under_test);

        EXPECT_CALL(root.actions, setup(_)).Times(1).RetiresOnSaturation();

        EXPECT_CALL(root.actions, loop(ContextNodeEquals(root.node)))
            .WillOnce(Return(Result{Status::Running, &node_under_test}))
            .RetiresOnSaturation();
        engine.step();
    }

    void expect_always_running(EngineResult result)
    {
        EXPECT_EQ(result.node_status, Status::Running);
        EXPECT_FALSE(result.is_running_leaf);
    }
};

TEST_F(PortTests, mandatory_port)
{
    setup(all_connections, port_m);

    EXPECT_CALL(mock_connection_m.actions, setup(_)).Times(1);

    expect_always_running(engine.step());
}

TEST_F(PortTests, mandatory_port_fail)
{
    setup(no_m_connection, port_m);

    EXPECT_CALL(root.actions, on_branch_complete(Status::Fail, _)).Times(1);

    expect_always_running(engine.step());
}

TEST_F(PortTests, optional_port)
{
    setup(all_connections, port_o);

    EXPECT_CALL(mock_connection_o.actions, setup(_)).Times(1);

    expect_always_running(engine.step());
}

TEST_F(PortTests, optional_port_fail)
{
    setup(no_o_connection, port_o);

    EXPECT_CALL(root.actions, on_branch_complete(Status::Success, _)).Times(1);

    expect_always_running(engine.step());
}