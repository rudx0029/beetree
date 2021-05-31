#include "beetree/facilities/filters/wheel-motion-filter.hpp"
#include "beetree/test-api/behavior-reqs.hpp"
#include "beetree/test-api/matchers/unit.hpp"

using namespace bte;
using namespace bte::units;
using namespace bte::units::literals;

using gtest::_;
using gtest::AtLeast;
using gtest::FloatEq;
using gtest::Return;
using test::UnitEquals;

class WheelMotionFilterTests : public test::BehaviorReqTest
{
protected:
    static void       SetUpTestCase() { Feature("beetree-startpk-motor-control"); }
    WheelMotionFilter filter;

    Clock::milliseconds dt         = 10_ms;
    units::Length       wheel_base = 100_mm;

    void SetUp() override { filter.configure(dt, wheel_base); }
};

TEST_F(WheelMotionFilterTests, circle)
{
    // TODO: What is this doing?

    units::AngVelocity expected_ang_velocity = 2_rps * units::PI;
    int                nsteps                = (1000_ms).count() / dt.count();

    for (int i = -nsteps / 2; i < nsteps / 2; i++)
    {
        WheelMotion input;
        input.left.accel    = make<mpss>(-i);
        input.left.velocity = make<mps>(-i);
        // input.left.distance = -2_mm;
        // input.left.velocity = input.left.distance / tf.dt;
        input.right.accel    = make<mpss>(i);
        input.right.velocity = make<mps>(i);
        // input.right.distance = 2_mm;
        // input.right.velocity = input.right.distance / tf.dt;

        Motion2D out = filter.apply(input);
        EXPECT_THAT(out.accel, UnitEquals(0_mpss));
        EXPECT_THAT(out.vel, UnitEquals(0_mps));
    }
}