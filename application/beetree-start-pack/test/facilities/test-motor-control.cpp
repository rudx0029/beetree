#include "beetree/facilities/filters/motor-control-filter-zero.hpp"
#include "beetree/test-api/behavior-reqs.hpp"

using namespace bte;
using namespace bte::units;
using namespace bte::units::literals;
using gtest::_;
using gtest::AtLeast;
using gtest::Return;

class MotorControlFilterTests : public test::BehaviorReqTest
{
protected:
    static void SetUpTestCase() { Feature("beetree-startpk-motor-control"); }

    MotorControlFilterZero motor_control;

    PID::Config pid_config;

    void SetUp() override
    {
        // configure the pipe

        pid_config.kp      = 1_scl;
        pid_config.ki      = 0_scl;
        pid_config.kd      = 0_scl;
        pid_config.ts      = 1_s;
        pid_config.max_cmd = 1000_scl;
        pid_config.min_cmd = -1000_scl;

        motor_control.configure(0_mmps, pid_config);
    }
};

/**
 * Scenario: MC Facility performs an outbound exchange,
 * commanding the PWM duty cycle from the commanded and measured velocities
 *
 * Given a MC Facility with only Proportional PID Control and 0 min velocity threshold
 * Given a measured velocity ranging negative to positive
 * Given a commanded velocity always at 0
 * When the facilities performs an outbound exchange
 * Then the PWM device is commanded with an absolute PWM value
 * Then the Motor Direction is set to forwards when PWM is positive
 * Then the Motor Direction is set to reverse when PWM is negative
 */
TEST_F(MotorControlFilterTests, whenInvokingFlow_thenThePWMIsCommanded)
{
    int total_iter = 100;

    // test assumes that min_vel_threshold is 0
    for (int idx = 0; idx < total_iter; idx++)
    {
        int       step               = idx - (total_iter / 2);
        int       expected_pwm       = abs(step);
        Direction expected_direction = (step >= 0) ? Direction::FORWARD : Direction::REVERSE;

        MotorControlInput input;
        input.commanded_velocity = make<mps>(step);
        input.measured_velocity  = 0_mps;

        MotorPWM output = motor_control.apply(input);

        EXPECT_EQ(as<scl>(output.motor_pwm), expected_pwm);
        EXPECT_EQ(output.motor_direction, expected_direction);
    }
}

/**
 * Scenario: MC Facility pid controller is bypassed and pwm is set to 0
 * when commanded velocity is less than threshold
 *
 * Given a MC Facility with only Proportional PID Control and 10 mmps min velocity threshold
 * Given a measured velocity ranging negative to positive
 * Given a commanded velocity always at 0
 * When the facilities performs an outbound exchange
 * Then the PWM device is commanded with an absolute PWM value
 * Then the Motor Direction is set to forwards when commanded velocity is positive
 * Then the Motor Direction is set to reverse when commanded velocity is negative
 */
TEST_F(MotorControlFilterTests,
       whenMinVelThresholdIsSetAndCommandIsGreaterOrEqual_thenThePWMIsCommanded)
{
    motor_control.configure(10_mps, pid_config);

    MotorControlInput input;
    input.measured_velocity  = 0_mps;
    input.commanded_velocity = -10_mps;

    MotorPWM out = motor_control.apply(input);

    EXPECT_TRUE(out.motor_pwm == 10_scl);
    EXPECT_TRUE(out.motor_direction == Direction::REVERSE);
}

/**
 * Scenario: MC Facility pid controller is bypassed and pwm is set to 0
 * when commanded velocity is less than threshold
 *
 * Given a MC Facility with only Proportional PID Control and 10 mmps min velocity threshold
 * Given a measured velocity ranging negative to positive
 * Given a commanded velocity always at 0
 * When the facilities performs an outbound exchange
 * Then the PWM device is commanded with an absolute PWM value
 * Then the Motor Direction is set to forwards when the commanded velocity is positive
 * Then the Motor Direction is set to reverse when the commanded velocity is negative
 */
TEST_F(MotorControlFilterTests, whenMinVelThresholdIsSetAndCommandIsLess_thenThePWMIsZero)
{
    motor_control.configure(10_mps, pid_config);

    MotorControlInput input;
    input.measured_velocity  = 0_mps;
    input.commanded_velocity = -9_mps;

    MotorPWM out = motor_control.apply(input);

    EXPECT_TRUE(out.motor_pwm == 0_scl);
    EXPECT_TRUE(out.motor_direction == Direction::REVERSE);
}