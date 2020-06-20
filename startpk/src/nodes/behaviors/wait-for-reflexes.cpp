//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/nodes/behaviors/wait-for-reflexes.hpp"
#include "beetree/btos/flags.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/nodes/blackboard.hpp"
#include "beetree/services/i-reflexes-service.hpp"
#include "beetree/startpk/tokens.hpp"

namespace bte {

static Result loop(Context&)
{
    auto status = Status::Fail;
    auto svc    = blackboard::get<IReflexesService>();

    // todo: look into timeout, unless we are guaranteed
    if (svc)
    {
        bool any_flags_active = flags::any(svc->model().current_reflexes);

        status = any_flags_active ? Status::Running : Status::Success;
    }

    return {status};
}

Recipe make_wait_for_reflexes() { return Builder(tokens::WaitForReflexesNode, loop).finalize(); }

}  // namespace bte