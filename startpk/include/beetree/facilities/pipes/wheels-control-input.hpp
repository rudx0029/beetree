#pragma once

#include "beetree/facilities/pipes/motor-control-input.hpp"

namespace bte {
struct WheelsControlInput
{
    MotorControlInput left_wheel;
    MotorControlInput right_wheel;
};
}  // namespace bte