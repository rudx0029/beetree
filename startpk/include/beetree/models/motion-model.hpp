#pragma once

#include "beetree/units/motion-profile.hpp"
#include "beetree/units/pose-2d.hpp"

namespace bte {
struct MotionModel
{
    bool                 is_stopped = true;
    units::MotionProfile measured;
    units::MotionProfile commanded;
};
}  // namespace bte