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
void   setup_go_to_relative(Context& c, const units::Coordinate&);
Recipe make_go_to_relative(delegate::Setup setup);

// translates from compile time to run time
template <const units::Coordinate& Position>
void setup_go_to_relative(Context& c)
{
    setup_go_to_relative(c, Position);
}

template <units::Coordinate PositionFnc(void)>
void setup_go_to_relative(Context& c)
{
    setup_go_to_relative(c, PositionFnc());
}

template <const units::Coordinate& Position>
Recipe make_go_to_relative()
{
    return make_go_to_relative(setup_go_to_relative<Position>);
}

template <units::Coordinate PositionFnc(void)>
Recipe make_go_to_relative()
{
    return make_go_to_relative(setup_go_to_relative<PositionFnc>);
}
}  // namespace bte