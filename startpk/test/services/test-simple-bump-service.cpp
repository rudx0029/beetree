//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/services/simple-bump-service.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/matchers/pose.hpp"
#include "beetree/test-api/matchers/time.hpp"
#include "beetree/test-api/matchers/unit.hpp"
#include "beetree/test-api/mocks/platform-mock.hpp"

using namespace bte;
using namespace units::literals;
using gtest::Return;
using test::PoseEquals;
using test::TimeEquals;
using test::UnitEquals;
using units::Angle;
using units::cast;
using units::Length;
using units::make;
using units::mscl;
using units::Pose2D;
using units::scl;

class SimpleBumpServiceTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("beetree-startpk-sensors"); }

    using BumpIterator = IBumpService::BumpIterator;
    test::PlatformMock platform_mock;
    BumpModel          model;
    SimpleBumpService  svc{model};
};

TEST_F(SimpleBumpServiceTests, is_bumped)
{
    Scenario << "The robot is bumped";
    Given << "a robot";

    When << "bumped";
    model.bump_zone = 1;

    Then << "it is bumped";
    EXPECT_TRUE(svc.is_bumping());

    When << "not bumpded";
    model.bump_zone = 0;

    Then << "it is not bumped";
    EXPECT_FALSE(svc.is_bumping());
}

TEST_F(SimpleBumpServiceTests, bump_incidence)
{
    Scenario << "The robot knows where it was bumped";

    Given << "A robot";
    When << "bumped";
    Then << "then angle is measured";

    for (int i = 0; i < 32; i++)
    {
        model.bump_zone = 1 << i;
        Angle angle     = svc.bump_incidence();

        // 0.196350 rad is equivalent to 360_deg/32.
        auto expected_angle = units::bound(196350_urad * make<scl>(i));

        EXPECT_THAT(angle, test::UnitEquals(expected_angle));
    }
}

TEST_F(SimpleBumpServiceTests, record_bumps)
{
    Scenario << "The robot has a history bumps";

    Given << "a robot";
    When << "bumped multiple times";
    Then << "the most recent bump is recorded";

    // precondition
    ASSERT_FALSE(svc.begin() != svc.end());

    for (int i = 0; i < 10 /*tries*/; i++)
    {
        // Given
        uint32_t      expected_time  = 0xDEADBEAF + i;  // std::chrono!!!
        units::Scalar i_mscl         = make<units::mscl>(i);
        Pose2D        expected_pose  = {135_mm + cast<Length>(i_mscl),
                                246_mm + cast<Length>(i_mscl),
                                357_mrad + cast<Angle>(i_mscl)};
        Angle         expected_angle = 789_mrad + cast<Angle>(i_mscl);

        // When
        EXPECT_CALL(*platform_mock, now_ms())
            .WillOnce(Return(expected_time))
            .RetiresOnSaturation();

        svc.record_bump(expected_pose, expected_angle);

        // Then
        auto iter = svc.begin();
        ASSERT_TRUE(iter != svc.end());  // iter must be valid before continuing
        EXPECT_THAT(svc.begin()->incidence, UnitEquals(expected_angle));
        EXPECT_THAT(svc.begin()->position, PoseEquals(expected_pose));
        EXPECT_THAT(svc.begin()->time, TimeEquals(expected_time));
    }
}

TEST_F(SimpleBumpServiceTests, clear_history)
{
    Scenario << "The robot can forget its bump history";

    Given << "a robot that has recorded bumps";
    When << "clearing its history";
    Then << "there are no recorded bumps";

    // load it up
    for (int i = 0; i < 10 /*tries*/; i++)
    {
        // Given
        uint32_t      t      = 0xDEADBEAF + i;  // std::chrono!!!
        units::Scalar i_mscl = make<units::mscl>(i);
        Pose2D        p      = {1_mm + cast<Length>(i_mscl),
                    2_mm + cast<Length>(i_mscl),
                    3_mrad + cast<Angle>(i_mscl)};
        Angle         a      = 4_mrad + cast<Angle>(i_mscl);

        ON_CALL(*platform_mock, now_ms()).WillByDefault(Return(t));

        svc.record_bump(p, a);
    }

    EXPECT_TRUE(svc.begin() != svc.end());

    svc.clear_history();

    EXPECT_FALSE(svc.begin() != svc.end());
}