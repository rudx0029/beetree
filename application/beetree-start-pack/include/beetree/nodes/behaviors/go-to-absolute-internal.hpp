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
#include "beetree/units/coordinate.hpp"

namespace bte {

// forward declarations
void setup_go_to_absolute(Context& c, const units::Coordinate&);

Recipe make_go_to_absolute(delegate::Setup setup);

template <const units::Coordinate& Position>
void setup_go_to_absolute(Context& c)
{
    setup_go_to_absolute(c, Position);
}

template <units::Coordinate PositionFnc(void)>
void setup_go_to_absolute(Context& c)
{
    setup_go_to_absolute(c, PositionFnc());
}

template <const units::Coordinate& Position>
Recipe make_go_to_absolute()
{
    return make_go_to_absolute(setup_go_to_absolute<Position>);
}
template <units::Coordinate PositionFnc(void)>
Recipe make_go_to_absolute()
{
    return make_go_to_absolute(setup_go_to_absolute<PositionFnc>);
}
}  // namespace bte