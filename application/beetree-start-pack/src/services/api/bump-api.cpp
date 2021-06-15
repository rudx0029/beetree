//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/services/api/bump-api.hpp"
#include "beetree/nodes/blackboard.hpp"
#include "beetree/services/i-bumper-service.hpp"

namespace bte {
using namespace units::literals;

Reflex BumpAPI::get_reflex() { return blackboard::get<IBumpService>()->get_reflex(); }

bool BumpAPI::is_bumping()
{
    auto svc = blackboard::get<IBumpService>();
    return svc && svc->is_bumping();
}

units::Angle BumpAPI::bump_incidence()
{
    units::Angle angle = 0_rad;
    auto         svc   = blackboard::get<IBumpService>();
    if (svc)
    {
        angle = svc->bump_incidence();
    }
    return angle;
}
}  // namespace bte