#pragma once

#include "beetree/facilities/pipes/encoder-reading.hpp"
#include "beetree/units/units.hpp"

namespace bte {
struct WheelEncoderReadings
{
    EncoderReading left;
    EncoderReading right;
};
}  // namespace bte