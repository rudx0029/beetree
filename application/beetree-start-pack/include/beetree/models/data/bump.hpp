//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/units/coordinate.hpp"
#include "beetree/units/units.hpp"

namespace bte {
struct Bump
{
    /// position of robot at the time of the bump
    units::Pose2D position;
    /// the angle at which the robot was struct
    /// TODO: define where the angle is measured from
    units::Angle incidence;
    /// the timestamp of the bump
    Clock::time_point time;
};
}  // namespace bte