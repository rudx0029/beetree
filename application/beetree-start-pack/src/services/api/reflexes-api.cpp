//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/services/api/reflexes-api.hpp"
#include "beetree/nodes/blackboard.hpp"
#include "beetree/services/i-reflexes-service.hpp"

namespace bte {
void ReflexesAPI::enable()
{
    auto svc = blackboard::update<IReflexesService>();
    if (svc) svc->enable();
}

void ReflexesAPI::disable()
{
    auto svc = blackboard::update<IReflexesService>();
    if (svc) svc->disable();
}

bool ReflexesAPI::are_enabled()
{
    auto svc = blackboard::get<IReflexesService>();
    return svc && svc->model().is_enabled;
}

bool ReflexesAPI::are_disabled()
{
    auto svc = blackboard::get<IReflexesService>();
    return !svc || !svc->model().is_enabled;
}

void ReflexesAPI::activate(const Reflex& reflex)
{
    auto svc = blackboard::update<IReflexesService>();
    if (svc) svc->activate_reflex(reflex);
}

void ReflexesAPI::deactivate_all()
{
    auto svc = blackboard::update<IReflexesService>();
    if (svc) svc->deactivate_all_reflexes();
}
}  // namespace bte