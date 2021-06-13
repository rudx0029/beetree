#pragma once

#include "beetree/facilities/filters/motor-control-filter-zero.hpp"
#include "beetree/facilities/pipes/wheels-control-input.hpp"
#include "beetree/facilities/pipes/wheels-pwm.hpp"

namespace bte {
class WheelsControlFilter
{
public:
    MotorControlFilterZero left;
    MotorControlFilterZero right;

    WheelsPWM apply(const WheelsControlInput& input);

private:
};
}  // namespace bte