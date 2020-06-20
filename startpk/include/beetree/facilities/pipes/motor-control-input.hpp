#pragma once

#include "beetree/facilities/facilities-defs.hpp"
#include "beetree/units/units.hpp"

namespace bte {
struct MotorControlInput
{
    units::Velocity commanded_velocity;
    units::Velocity measured_velocity;
};
}  // namespace bte