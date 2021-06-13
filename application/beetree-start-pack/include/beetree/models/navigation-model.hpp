//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/units/pose-2d.hpp"

namespace bte {
///
/// Public data model for INavigationService
///
struct NavigationModel
{
    units::Pose2D measured_pose;
    units::Pose2D commanded_pose;
};
}  // namespace bte