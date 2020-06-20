//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/facilities/filters/wheels-control-filter.hpp"

namespace bte {

WheelsPWM WheelsControlFilter::apply(const WheelsControlInput& in)
{
    MotorPWM left_pwm  = left.apply(in.left_wheel);
    MotorPWM right_pwm = right.apply(in.right_wheel);
    return {left_pwm, right_pwm};
}
}  // namespace bte