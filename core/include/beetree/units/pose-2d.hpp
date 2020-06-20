//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/units/units.hpp"

namespace bte {
namespace units {

namespace {
using namespace literals;
}

struct Pose2D
{
    Position x       = 0_m;
    Position y       = 0_m;
    Angle    heading = 0_rad;

    constexpr Pose2D() = default;
    constexpr Pose2D(const Position& x_, const Position& y_, const Angle& heading_)
        : x(x_), y(y_), heading(heading_)
    {}
};
}  // namespace units
}  // namespace bte