#pragma once

#include "beetree/facilities/facilities-defs.hpp"
#include "beetree/units/units.hpp"

namespace bte {
struct Motion
{
    units::Length   distance;  /// distance travelled (since last update, displacement)
    units::Velocity velocity;
    units::Accel    accel;
};
}  // namespace bte