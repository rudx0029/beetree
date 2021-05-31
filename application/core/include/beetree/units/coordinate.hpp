//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/units/pose-2d.hpp"
#include "beetree/units/units.hpp"

namespace bte {
namespace units {

namespace {
using namespace literals;
}

struct Coordinate
{
    Position x = 0_m;
    Position y = 0_m;

    constexpr Coordinate() = default;
    constexpr Coordinate(const Position& x_, const Position& y_) : x(x_), y(y_) {}
};
}  // namespace units
}  // namespace bte