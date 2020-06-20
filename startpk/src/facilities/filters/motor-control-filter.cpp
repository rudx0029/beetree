#include "beetree/facilities/filters/motor-control-filter.hpp"

namespace bte {

using namespace units;
using namespace units::literals;

void MotorControlFilter::configure(Velocity min_vel_threshold, const PID::Config& pid)
{
    m_min_vel_threshold = min_vel_threshold;
    m_pid.configure(pid);
}

MotorPWM MotorControlFilter::apply(const MotorControlInput& in)
{
    Scalar    pwm             = 0_scl;
    Direction motor_direction = Direction::FORWARD;
    if (abs(in.commanded_velocity) >= m_min_vel_threshold)
    {
        pwm = m_pid.step(cast<Scalar>(in.commanded_velocity), cast<Scalar>(in.measured_velocity));
    }
    else
    {
        // run the pid with command_velocity to 0 but do not update the pwm
        m_pid.step(0_scl, cast<Scalar>(in.measured_velocity));
    }

    //
    // The sign of the pwm determines the direction of the robot
    // If positive then set the forward flag, else set the reverse flag
    //
    if (pwm >= 0_scl)
    {
        // forwards direction
        motor_direction = Direction::FORWARD;
    }
    else
    {
        // reverse
        pwm             = -pwm;
        motor_direction = Direction::REVERSE;
    }

    return {pwm, motor_direction};
}
}  // namespace bte