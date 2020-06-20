#pragma once

#include "beetree/facilities/pipes/motion.hpp"
#include "beetree/units/pose-2d.hpp"
#include "beetree/units/units.hpp"

namespace bte {
struct Motion2D
{
    units::Position x;
    units::Position y;
    units::Angle    heading;

    units::Velocity    vel;
    units::AngVelocity ang_vel;

    units::Accel    accel;
    units::AngAccel ang_accel;
};
}  // namespace bte