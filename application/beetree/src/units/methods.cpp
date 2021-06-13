//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/units/methods.hpp"

namespace bte {
namespace units {
Coordinate to_rel_coord(const Coordinate& abs_point, const Pose2D& frame)
{
    // translate point in frame's reference
    Coordinate t = {abs_point.x - frame.x, abs_point.y - frame.y};
    // rotate point back

    Scalar s = sin(-frame.heading);
    Scalar c = cos(-frame.heading);
    return {t.x * c - t.y * s, t.x * s + t.y * c};
}

Coordinate to_abs_coord(const Coordinate& relative_point, const Pose2D& frame)
{
    Scalar s = sin(frame.heading);
    Scalar c = cos(frame.heading);

    // rotate point
    Length xnew = relative_point.x * c - relative_point.y * s;
    Length ynew = relative_point.x * s + relative_point.y * c;

    // translate point back to absolute
    return {frame.x + xnew, frame.y + ynew};
}

Length distance(const Coordinate& a, const Coordinate& b, units::Length* dx, units::Length* dy)
{
    Length dy_ = a.y - b.y;
    Length dx_ = a.x - b.x;

    if (dx)
    {
        *dx = dx_;
    }
    if (dy)
    {
        *dy = dy_;
    }

    return sqrt(dy_ * dy_ + dx_ * dx_);
}

Angle to_abs_heading(Angle relative, const Pose2D& frame) { return frame.heading + relative; }

}  // namespace units
}  // namespace bte