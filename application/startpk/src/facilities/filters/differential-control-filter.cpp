//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/facilities/filters/differential-control-filter.hpp"

namespace bte {
using Output = DifferentialControlFilter::Output;

using units::AngVelocity;
using units::Length;
using units::Velocity;

struct VelocityLR
{
    Velocity left;
    Velocity right;
};

static VelocityLR to_left_right(const units::MotionProfile& mp, units::Length wheel_base)
{
    Velocity    v = mp.velocity;
    AngVelocity w = mp.angularVelocity;

    Velocity vel_l = v - (w * wheel_base) / 2_scl;
    Velocity vel_r = (w * wheel_base) + vel_l;

    return {vel_l, vel_r};
}

Output DifferentialControlFilter::apply(Input input)
{
    VelocityLR commanded = to_left_right(input.commanded, m_wheel_base);
    VelocityLR measured  = to_left_right(input.measured, m_wheel_base);

    return WheelsControlInput{{commanded.left, measured.left}, {commanded.right, measured.right}};
}

void DifferentialControlFilter::configure(units::Length wheel_base) { m_wheel_base = wheel_base; }
}  // namespace bte