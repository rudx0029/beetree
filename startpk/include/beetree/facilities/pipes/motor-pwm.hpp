#pragma once

#include "beetree/facilities/facilities-defs.hpp"
#include "beetree/units/units.hpp"

namespace bte {
struct MotorPWM
{
    units::Scalar motor_pwm;
    Direction     motor_direction;
};
}  // namespace bte