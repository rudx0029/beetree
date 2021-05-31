//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/context.hpp"
#include "beetree/engine/node.hpp"
#include "beetree/engine/recipe.hpp"
#include "beetree/units/units.hpp"

namespace bte {

// forward declarations
void   setup_rotate_relative(Context& c, units::Angle target);
void   setup_rotate_absolute(Context& c, units::Angle target);
Recipe make_rotate_absolute(delegate::Setup setup);
Recipe make_rotate_relative(delegate::Setup setup);

template <const units::Angle& Target>
void setup_rotate_relative(Context& c)
{
    setup_rotate_relative(c, Target);
}

template <const units::Angle& Target>
void setup_rotate_absolute(Context& c)
{
    setup_rotate_absolute(c, Target);
}

template <units::Angle TargetFnc(void)>
void setup_rotate_relative(Context& c)
{
    setup_rotate_relative(c, TargetFnc());
}

template <units::Angle TargetFnc(void)>
void setup_rotate_absolute(Context& c)
{
    setup_rotate_absolute(c, TargetFnc());
}

template <const units::Angle& Target>
Recipe make_rotate_relative()
{
    return make_rotate_relative(setup_rotate_relative<Target>);
}

template <units::Angle TargetFnc(void)>
Recipe make_rotate_relative()
{
    return make_rotate_relative(setup_rotate_relative<TargetFnc>);
}

template <const units::Angle& Target>
Recipe make_rotate_absolute()
{
    return make_rotate_absolute(setup_rotate_absolute<Target>);
}

template <units::Angle TargetFnc(void)>
Recipe make_rotate_absolute()
{
    return make_rotate_absolute(setup_rotate_absolute<TargetFnc>);
}

}  // namespace bte