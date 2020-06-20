#pragma once

#include "beetree/controllers/pid.hpp"
#include "beetree/facilities/pipes/motor-control-input.hpp"
#include "beetree/facilities/pipes/motor-pwm.hpp"

namespace bte {
class MotorControlFilterZero
{
public:
    void     configure(units::Velocity min_vel_threshold, const PID::Config& pid);
    MotorPWM apply(const MotorControlInput& input);

private:
    units::Velocity measure_velocity(Clock::milliseconds dt);
    units::Accel measure_accel(units::Velocity cur, units::Velocity prev, Clock::milliseconds dt);

    units::Velocity   m_min_vel_threshold;
    PID               m_pid;
    Clock::time_point m_last_time;
};
}  // namespace bte