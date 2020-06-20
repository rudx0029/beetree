//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/nodes/behaviors/null-odometry.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/nodes/blackboard.hpp"
#include "beetree/services/i-navigation-service.hpp"
#include "beetree/startpk/tokens.hpp"

namespace bte {

static Result loop(Context&)
{
    Status status = Status::Fail;

    auto svc = blackboard::update<INavigationService>();
    if (svc)
    {
        svc->null_odometry();
        status = Status::Success;
    }
    return status;
}

Recipe make_null_odometry() { return Builder(tokens::NullOdometryNode, loop).finalize(); }
}  // namespace bte