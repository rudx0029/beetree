#pragma once

#include "beetree/facilities/pipes/motor-pwm.hpp"

namespace bte {
struct WheelsPWM
{
    MotorPWM left;
    MotorPWM right;
};
}  // namespace bte