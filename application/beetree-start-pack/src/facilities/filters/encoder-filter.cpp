//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/facilities/filters/encoder-filter.hpp"

namespace bte {
using namespace units;
using namespace units::literals;

void EncoderFilter::configure(Clock::milliseconds dt,
                              units::Length       wheel_dist_per_tick,
                              units::Scalar       reload)
{
    m_dt                  = dt;
    m_wheel_dist_per_tick = wheel_dist_per_tick;
    m_reload              = reload;
    m_last_ticks          = 0_scl;
    m_last_vel            = 0_mps;
}

units::Length EncoderFilter::measure_distance(const EncoderReading& in) const
{
    units::Scalar count;
    units::Length distance;

    if (in.ticks > m_last_ticks)
    {
        count = in.ticks - m_last_ticks;
    }
    else if (in.ticks < m_last_ticks)
    {
        count = in.ticks + (m_reload - m_last_ticks);
    }

    if (in.direction == Direction::FORWARD)
    {
        distance = count * m_wheel_dist_per_tick;
    }
    else
    {
        distance = -count * m_wheel_dist_per_tick;
    }

    return distance;
}

Velocity EncoderFilter::measure_velocity(units::Length delta_len) const
{
    return delta_len / m_dt;
}

Accel EncoderFilter::measure_accel(Velocity cur, Velocity prev) const
{
    return (cur - prev) / m_dt;
}

Motion EncoderFilter::apply(const EncoderReading& in)
{
    //
    // the wheel spec is in um.. 273um our ticks will be in mm.
    // If i convert as scl, the result is 0 because the working value is in
    // meters (0.000xxxyyy) mm multiplies it by 1000.
    //

    auto distance = measure_distance(in);
    auto velocity = measure_velocity(distance);
    auto accel    = measure_accel(velocity, m_last_vel);

    m_last_ticks = in.ticks;
    m_last_vel   = velocity;

    return {distance, velocity, accel};
}

void EncoderFilter::reset()
{
    m_last_ticks = 0_scl;
    m_last_vel   = 0_mps;
}
}  // namespace bte