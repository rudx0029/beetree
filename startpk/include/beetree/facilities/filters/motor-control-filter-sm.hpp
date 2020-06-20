#pragma once

#include "beetree/controllers/pid.hpp"
#include "beetree/facilities/pipes/motor-control-input.hpp"
#include "beetree/facilities/pipes/motor-pwm.hpp"

namespace bte {
class MotorControlFilterSM
{
public:
    void     configure(units::Velocity min_vel_threshold, const PID::Config& pid);
    MotorPWM apply(const MotorControlInput& input);

    enum class motionStates
    {
        NO_MOTION,
        START_MOTION_FWD,
        START_MOTION_REV,
        CONTINUE_MOTION_FWD,
        CONTINUE_MOTION_REV,
        ZERO_CROSS_FWD,
        ZERO_CROSS_REV
    };

private:
    MotorPWM sm(const MotorControlInput& in);
    MotorPWM no_motion(const MotorControlInput& in);
    MotorPWM start_motion_fwd(const MotorControlInput& in);
    MotorPWM continue_motion_fwd(const MotorControlInput& in);
    MotorPWM zero_cross_fwd(const MotorControlInput& in);
    MotorPWM start_motion_rev(const MotorControlInput& in);
    MotorPWM continue_motion_rev(const MotorControlInput& in);
    MotorPWM zero_cross_rev(const MotorControlInput& in);

    units::Velocity measure_velocity(Clock::milliseconds dt);
    units::Accel measure_accel(units::Velocity cur, units::Velocity prev, Clock::milliseconds dt);

    units::Velocity   m_min_vel_threshold;
    PID               m_pid;
    Clock::time_point m_last_time;
    motionStates      m_active      = motionStates::NO_MOTION;
    uint32_t          m_state_count = 0;
};

}  // namespace bte