//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/services/simple-navigation-service.hpp"
#include "beetree/test/behavior-reqs.hpp"
#include "beetree/test/matchers/pose.hpp"
#include "beetree/test/matchers/unit.hpp"
#include "beetree/test/mocks/platform-mock.hpp"

#include "fakes/fake-motion-service.hpp"

using namespace bte;
using namespace bte::units::literals;
using gtest::_;
using gtest::NiceMock;
using gtest::Return;
using test::PlatformMock;
using test::PoseEquals;
using test::UnitEquals;
using test::UnitGt;
using test::internal::FakeMotionService;
using units::Angle;
using units::AngVelocity;
using units::cast;
using units::Length;

class SimpleNavigationServiceTest : public test::BehaviorReqTest
{
public:
    static void SetUpTestCase() { Feature("Navigation"); }

protected:
    PlatformMock            platform_mock;
    NavigationModel         nav_model;
    SimpleNavigationModel   nav_internal_model;
    SimpleNavigationService nav_svc{nav_model, nav_internal_model};
    FakeMotionService       fake_motion_svc;

    Length      near_pos_threshold = 100_mm;
    Length      at_pos_threshold   = 50_mm;
    AngVelocity ang_vel_threshold  = 200_mradps;
    Angle       rotate_threshold   = 2_deg;
    float       tolerance          = 0.001f;

    void SetUp() override
    {
        SimpleGoToPositionTask::Config goto_task_config;
        goto_task_config.travel_velocity         = 200_mmps;
        goto_task_config.at_pos_threshold        = at_pos_threshold;
        goto_task_config.near_pos_threshold      = near_pos_threshold;
        goto_task_config.goal_pid_config.kp      = 1_scl;
        goto_task_config.goal_pid_config.ts      = 1_s;
        goto_task_config.goal_pid_config.max_cmd = 1000_scl;
        goto_task_config.goal_pid_config.min_cmd = -1000_scl;

        SimpleRotateTask::Config rotate_task_config;
        rotate_task_config.ang_vel_threshold = ang_vel_threshold;
        rotate_task_config.threshold         = rotate_threshold;
        rotate_task_config.pid.kp            = 1_scl;
        rotate_task_config.pid.ki            = 0_scl;
        rotate_task_config.pid.kd            = 0_scl;
        rotate_task_config.pid.bias          = 0_scl;
        rotate_task_config.pid.ts            = 1_s;
        rotate_task_config.pid.max_cmd       = 1000_scl;
        rotate_task_config.pid.min_cmd       = -1000_scl;

        nav_svc.configure(fake_motion_svc, goto_task_config, rotate_task_config);
    }
};

TEST_F(SimpleNavigationServiceTest, null_odometry)
{
    Scenario << "A node wants to null/reset odometry";
    Given << "a navigation service";
    nav_internal_model.is_null_odometry_signaled = false;
    nav_model.measured_pose                      = {1_m, 1_m, 1_rad};

    When << "a node requests to null odometry";
    nav_svc.null_odometry();

    Then << "the service has reset/nulled odometry";
    EXPECT_TRUE(nav_internal_model.is_null_odometry_signaled);
    EXPECT_THAT(nav_svc.model().measured_pose, PoseEquals({0_m, 0_m, 0_rad}));
}

TEST_F(SimpleNavigationServiceTest, far_from_go_to_target)
{
    Scenario << "Robot goes to a target";

    Given << "a robot going to a target";
    When << "the robot is not near the target";
    // setup commanded position in nav
    nav_model.measured_pose = {0_m, 0_m, 0_rad};
    Task t                  = nav_svc.go_to({at_pos_threshold + 1_mm, 0_mm}, 1_s);

    Then << "the robot continues to go to the target";
    EXPECT_TRUE(t.run());
}

TEST_F(SimpleNavigationServiceTest, reaches_go_to_target)
{
    Scenario << "Robot goes to a target";

    Given << "a robot going to a target";
    When << "the robot is near the target";
    // setup commanded position in nav
    nav_model.measured_pose = {0_m, 0_m, 0_rad};
    Task t                  = nav_svc.go_to({at_pos_threshold - 1_mm, 0_mm}, 1_s);

    Then << "the robot stops going to the target";
    EXPECT_FALSE(t.run());
}

MATCHER_P2(WithVelocityGtAndAngVel, velocity, ang_vel, "")
{
    return (arg.angularVelocity == ang_vel) && (arg.velocity > velocity);
}

TEST_F(SimpleNavigationServiceTest, go_to_target_commands_move)
{
    Scenario << "The robot goes to a target";

    Given << "a robot at a location";
    nav_model.measured_pose = {0_m, 0_m, 5_deg};

    When << "commanded to go to a target";
    Task t = nav_svc.go_to({near_pos_threshold + 1_mm, 0_mm}, 1_s);
    t.run();

    Then << "the robot commands itself to move";
    // Expecting the motion profiles velocity to be greater than 0
    auto actual_vel = fake_motion_svc.model().commanded.velocity;
    EXPECT_THAT(actual_vel, UnitGt(0_mps));

    // Given the PID settings, expecting the commanded angular velocity to the
    // negative of the robot's measured heading
    auto actual_ang_vel   = fake_motion_svc.model().commanded.angularVelocity;
    auto expected_ang_vel = cast<AngVelocity>(-nav_model.measured_pose.heading);
    EXPECT_THAT(actual_ang_vel, UnitEquals(expected_ang_vel));
}

TEST_F(SimpleNavigationServiceTest, rotate_to_heading_still_far_from_heading)
{
    Scenario << "Robot rotates to a heading";

    Given << "A robot";

    When << "rotating to a heading";
    When << "the current heading is far from the target heading";
    nav_model.measured_pose = {0_m, 0_m, rotate_threshold + 1_deg};
    Task t                  = nav_svc.rotate_to(0_deg, 1_s);

    Then << "the robot continues to rotoate";
    EXPECT_TRUE(t.run());
}

TEST_F(SimpleNavigationServiceTest, rotate_to_heading_near_heading)
{
    Scenario << "Robot rotates to a heading";

    Given << "A robot";

    When << "rotating to a heading";
    When << "the current heading is near to the target heading";
    nav_model.measured_pose = {0_m, 0_m, rotate_threshold - 1_deg};
    Task t                  = nav_svc.rotate_to(0_deg, 1_s);

    Then << "the robot stops rotating";
    EXPECT_FALSE(t.run());
}

TEST_F(SimpleNavigationServiceTest, rotate_to_heading_ang_velocity_too_high)
{
    Scenario << "Robot rotates to a heading";

    Given << "A robot";

    When << "rotating to a heading";
    When << "the current heading is near to the target heading";
    When << "the angular velocity is too high";
    nav_model.measured_pose                             = {0_m, 0_m, rotate_threshold + 1_deg};
    fake_motion_svc.fake_model.measured.angularVelocity = ang_vel_threshold - 1_mradps;
    Task t                                              = nav_svc.rotate_to(0_deg, 1_s);

    Then << "the robot continues to rotoate";
    EXPECT_TRUE(t.run());
}

TEST_F(SimpleNavigationServiceTest, rotate_to_heading_ang_velocity_is_low)
{
    Scenario << "Robot rotates to a heading";

    When << "rotating to a heading";
    When << "the current heading is near to the target heading";
    When << "the angular velocity is low";
    nav_model.measured_pose                             = {0_m, 0_m, rotate_threshold - 1_deg};
    fake_motion_svc.fake_model.measured.angularVelocity = ang_vel_threshold - 1_mradps;
    Task t                                              = nav_svc.rotate_to(0_deg, 1_s);

    Then << "the robot stops rotating";
    EXPECT_FALSE(t.run());
}

TEST_F(SimpleNavigationServiceTest, rotate_to_heading_command_motion)
{
    Scenario << "Robot rotates to a heading";

    When << "commanded to rotate to a heading";
    nav_model.measured_pose = {0_m, 0_m, rotate_threshold + 1_deg};
    Task t                  = nav_svc.rotate_to(0_deg, 1_s);

    t.run();

    Then << "the robot commands itself to move";
    auto actual_ang_vel   = fake_motion_svc.model().commanded.angularVelocity;
    auto expected_ang_vel = -cast<AngVelocity>(rotate_threshold + 1_deg);
    EXPECT_THAT(actual_ang_vel, UnitEquals(expected_ang_vel));
}
