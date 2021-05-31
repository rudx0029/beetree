//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/units/motion-profile.hpp"

namespace bte {
struct DifferentialControlInput
{
    units::MotionProfile commanded;
    units::MotionProfile measured;
};
}  // namespace bte