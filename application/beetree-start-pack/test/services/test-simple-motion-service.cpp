//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/services/simple-motion-service.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/gtest-ns.hpp"
#include "beetree/test-api/matchers/motion-profile.hpp"

using namespace bte;
using namespace units::literals;
using test::MotionProfileEquals;
using units::Accel;
using units::AngVelocity;
using units::cast;
using units::make;
using units::MotionProfile;
using units::Scalar;
using units::scl;
using units::Velocity;

class SimpleMotionServiceTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { return Feature("Motion"); }

    MotionModel         model;
    SimpleMotionService svc{model};
};

TEST_F(SimpleMotionServiceTests, move)
{
    Scenario << "The robot moves";
    Given << "a robot";
    When << "moving";
    Then << "moves according to the motion profile";

    for (int i = 0; i < 10; i++)
    {
        MotionProfile expected;
        Scalar        i_scl = make<scl>(i);

        expected.velocity        = 123_mps + cast<Velocity>(i_scl);
        expected.acceleration    = 456_mpss + cast<Accel>(i_scl);
        expected.angularVelocity = 789_radps + cast<AngVelocity>(i_scl);

        svc.move(expected);

        EXPECT_THAT(svc.model().commanded, MotionProfileEquals(expected));
    }
}

TEST_F(SimpleMotionServiceTests, stop)
{
    Scenario << "The robot stops";

    Given << "a moving robot";
    svc.move({123_mps, 456_mpss, 789_radps});

    When << "stopping";
    svc.stop();

    Then << "the robot stops according to the motion profile";
    EXPECT_THAT(svc.model().commanded, MotionProfileEquals({0_mps, 0_mpss, 0_radps}));
}