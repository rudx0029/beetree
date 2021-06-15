//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/facilities/filters/wheel-motion-filter.hpp"

namespace bte {

using namespace units;
using namespace units::literals;

void WheelMotionFilter::configure(Clock::milliseconds ts, units::Length wheel_base)
{
    m_ts         = ts;
    m_wheel_base = wheel_base;
}

units::AngAccel WheelMotionFilter::calc_alpha(const WheelMotion& input)
{
    return (input.right.accel - input.left.accel) / m_wheel_base;
}

units::AngVelocity WheelMotionFilter::calc_omega(const WheelMotion& input)
{
    return (input.right.velocity - input.left.velocity) / m_wheel_base;
}

units::Angle WheelMotionFilter::calc_theta(const WheelMotion& input, AngVelocity w, Angle theta_0)
{
    // equation:  d/dt theta = w => integrating: theta = w*t + w_0
    auto theta = w * m_ts + theta_0;
    return units::bound(theta);
}

Position WheelMotionFilter::calc_x(const WheelMotion& input,
                                   Velocity           vel,
                                   Angle              theta,
                                   Position           x_0)
{
    return vel * m_ts * cos(theta) + x_0;
}

Position WheelMotionFilter::calc_y(const WheelMotion& input,
                                   Velocity           vel,
                                   Angle              theta,
                                   Position           y_0)
{
    return vel * m_ts * sin(theta) + y_0;
}

Motion2D WheelMotionFilter::apply(const WheelMotion& input)
{
    Motion2D out;

    out.ang_accel = calc_alpha(input);
    out.ang_vel   = calc_omega(input);
    out.heading   = calc_theta(input, out.ang_vel, m_last_theta);
    out.vel       = (input.right.velocity + input.left.velocity) / 2_scl;
    out.accel     = (input.right.accel + input.left.accel) / 2_scl;
    out.x         = calc_x(input, out.vel, out.heading, m_last_x);
    out.y         = calc_y(input, out.vel, out.heading, m_last_y);

    // update state
    m_last_theta = out.heading;
    m_last_x     = out.x;
    m_last_y     = out.y;

    return out;
}

void WheelMotionFilter::reset()
{
    m_last_theta = 0_rad;
    m_last_x     = 0_m;
    m_last_y     = 0_m;
}
}  // namespace bte