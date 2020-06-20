//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/facilities/filters/motor-control-filter-zero.hpp"

namespace bte {

using namespace units;
using namespace units::literals;

void MotorControlFilterZero::configure(Velocity min_vel_threshold, const PID::Config& pid)
{
    m_min_vel_threshold = min_vel_threshold;
    m_pid.configure(pid);
}

MotorPWM MotorControlFilterZero::apply(const MotorControlInput& in)
{
    Scalar    pwm = 0_scl;
    Direction motor_direction;

    if (in.commanded_velocity >= 0_mmps)
    {
        motor_direction = Direction::FORWARD;
    }
    else
    {
        motor_direction = Direction::REVERSE;
    }

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
    // Direction of rotation is determined by the command.
    // But we have to look for overshoot
    //
    if (pwm >= 0_scl)
    {
        //
        // our commanded velocity is positive
        //
        if (motor_direction == Direction::REVERSE)
        {
            //
            // drop PWM to 0 as we have overshoot from negative to positive
            // Let it coast - this can cause bucking if P is too high
            //
            pwm = 0_scl;
        }
    }
    else
    {
        //
        // Our commanded velocity is positive
        //
        if (motor_direction == Direction::FORWARD)
        {
            //
            // we have overshoot, so set the pwm to 0
            // This will let it coast, but can cause bucking if P is too high
            //
            pwm = 0_scl;
        }
        else
        {
            //
            // Need to make a positive value for pwm.
            //
            // so reverse is direction
            pwm = -pwm;
        }
    }

    return {pwm, motor_direction};
}
}  // namespace bte