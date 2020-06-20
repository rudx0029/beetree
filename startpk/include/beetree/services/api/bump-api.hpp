//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/models/data/reflex.hpp"
#include "beetree/units/units.hpp"

namespace bte {
struct BumpAPI
{
    static bool         is_bumping();
    static Reflex       get_reflex();
    static units::Angle bump_incidence();
};
}  // namespace bte