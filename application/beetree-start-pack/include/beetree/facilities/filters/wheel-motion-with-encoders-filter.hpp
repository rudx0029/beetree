#pragma once

#include "beetree/facilities/filters/encoder-filter.hpp"
#include "beetree/facilities/filters/wheel-motion-filter.hpp"
#include "beetree/facilities/pipes/wheel-encoder-readings.hpp"

namespace bte {
class WheelMotionWithEncodersFilter
{
public:
    EncoderFilter     left_encoder;
    EncoderFilter     right_encoder;
    WheelMotionFilter diff_drive;

    Motion2D apply(const WheelEncoderReadings& input);

private:
};
}  // namespace bte