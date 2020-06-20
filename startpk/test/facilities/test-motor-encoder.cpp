#include "beetree/facilities/filters/encoder-filter.hpp"
#include "beetree/test/behavior-reqs.hpp"

using namespace bte;
using namespace bte::units;
using namespace bte::units::literals;
using gtest::_;
using gtest::AtLeast;
using gtest::Return;

class MotorEncoderTests : public test::BehaviorReqTest
{
protected:
    static void   SetUpTestCase() { Feature("beetree-startpk-motor-control"); }
    EncoderFilter motor_encoder_read;

    Clock::milliseconds time_interval_ms = 2_ms;
    Length              wheel_spec       = 1000_um;

    void SetUp() override { motor_encoder_read.configure(time_interval_ms, wheel_spec); }
};

/**
 * Scenario: MC Facility performs an inbound exchange,
 * reading encoder ticks and calculating velocity at a set interval
 *
 * Given a motor operating in the forward direction
 * When the measured velocity is calculated
 * Then the measured velocity is positive and stored in the registry
 *
 * Given a motor operating in the reverse direction
 * When the measured velocity is calculated
 * Then the measured velocity is negative and stored in the registry
 */
TEST_F(MotorEncoderTests, whenInvokingExchangeInbound_thenTheMeasuredVelocityIsSetInTheBank)
{
    int ms_per_sec         = 1000;
    int ticks_per_interval = 10;
    int total_iter         = 10;

    for (int idx = 1; idx <= total_iter; idx++)
    {
        int       step = idx - (total_iter / 2);
        int       sign = step >= 0 ? 1 : -1;
        Direction dir  = step >= 0 ? Direction::FORWARD : Direction::REVERSE;
        int       expected_velocity_mmps =
            sign * (ticks_per_interval * ms_per_sec) / time_interval_ms.count();

        EncoderReading input;

        input.ticks     = make<scl>(idx * ticks_per_interval);
        input.direction = dir;

        Motion out = motor_encoder_read.apply(input);

        EXPECT_EQ(as<mmps>(out.velocity), expected_velocity_mmps);
    }
}

TEST_F(MotorEncoderTests, Encoder_whenInvokingExchangeInbound_thenTheMotorEncoderFwdIsSetInTheBank)
{
    EncoderReading input;

    input.ticks     = 222_scl;
    input.direction = Direction::FORWARD;

    Motion out = motor_encoder_read.apply(input);

    EXPECT_EQ(as<mm>(out.distance), 222);
}

TEST_F(MotorEncoderTests, Sensor_whenInvokingExchangeInbound_thenTheMotorEncoderRevIsSetInTheBank)
{
    EncoderReading input;

    input.ticks     = 222_scl;
    input.direction = Direction::REVERSE;

    Motion out = motor_encoder_read.apply(input);

    EXPECT_EQ(as<mm>(out.distance), -222);
}
