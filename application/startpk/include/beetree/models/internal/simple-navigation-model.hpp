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
/// Internal data model for SimpleNavigationService
///
struct SimpleNavigationModel
{
    bool is_null_odometry_signaled = false;
};
}  // namespace bte
