#include "beetree/controllers/goal-controller.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/matchers/unit.hpp"

using namespace bte;
using namespace bte::units;
using namespace bte::units::literals;
using namespace bte::test;

class GoalControllerTests : public BehaviorReqTest
{
protected:
    static void    SetUpTestCase() { Feature("beetree-startpk-controllers"); }
    PID::Config    pid_cfg;
    GoalController ctrl;

    Velocity travel_vel     = 200_mmps;
    Length   threshold_dist = 100_mm;

    float tolerance = 0.001f;

    void SetUp() override
    {
        pid_cfg.kp      = 1_scl;
        pid_cfg.ts      = 1_s;
        pid_cfg.max_cmd = 1000_scl;
        pid_cfg.min_cmd = -1000_scl;

        ctrl.configure(pid_cfg, threshold_dist, travel_vel);
    }
};

TEST_F(GoalControllerTests, whenGoalIsFar_thenVelocityIsTravelVel)
{
    Pose2D target{2_scl * threshold_dist, 0_mm, 0_rad};  // target at 300 mm
    Pose2D current{threshold_dist, 0_mm, 0_rad};         // current at 200 mm
    Pose2D initial{0_mm, 0_mm, 0_rad};

    ctrl.reset(target, initial);
    MotionProfile mp = ctrl.step(target, current);

    EXPECT_THAT(mp.velocity, UnitNear(travel_vel, 1_mmps));
}

TEST_F(GoalControllerTests, whenGoalIsNear_thenVelocityIsRatioOfDistanceAndThreshold)
{
    Length test_interval = threshold_dist / 10_scl;
    Pose2D target{threshold_dist, 0_mm, 0_rad};  // target at 300 mm
    Pose2D initial{-10_scl * threshold_dist, 0_mm, 0_rad};
    ctrl.reset(target, initial);

    for (int i = 0; i < 10; i++)
    {
        Pose2D   current{make<scl>(i) * test_interval, 0_mm, 0_rad};
        Velocity expected_vel =
            travel_vel * ((threshold_dist - make<scl>(i) * test_interval) / threshold_dist);

        MotionProfile mp = ctrl.step(target, current);
        EXPECT_THAT(mp.velocity, UnitNear(expected_vel, 1_mmps));
    }
}

TEST_F(GoalControllerTests,
       whenRobotIsNotDirectlyHeadingToGoal_thenAngularVelocityIsSetInOppositeDirectionOfHeading)
{
    Angle test_interval = 5_deg;
    Angle test_theta    = -30_deg;
    Angle test_end      = 30_deg;

    while (test_theta <= test_end)
    {
        Pose2D target{threshold_dist + 10_mm, 0_mm, 0_rad};
        Pose2D current{0_mm, 0_mm, test_theta};

        ctrl.reset(target, current);
        MotionProfile mp = ctrl.step(target, current);

        EXPECT_THAT(cast<Angle>(mp.angularVelocity), UnitNear(-test_theta, 1_mrad));

        test_theta += test_interval;
    }
}