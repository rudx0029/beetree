//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/facilities/filters/wheel-motion-with-encoders-filter.hpp"

namespace bte {
Motion2D WheelMotionWithEncodersFilter::apply(const WheelEncoderReadings& in)
{
    auto left_motion  = left_encoder.apply(in.left);
    auto right_motion = right_encoder.apply(in.right);

    return diff_drive.apply({left_motion, right_motion});
}
}  // namespace bte