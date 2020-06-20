//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/units/coordinate.hpp"
#include "beetree/units/pose-2d.hpp"

namespace bte {
namespace units {
///
/// Converts a pose into a coordinate, effectively dropping the pose's heading.
///
/// @param p the pose to convert to a coordinate
/// @return  the pose as a coordinate
///
inline constexpr Coordinate to_coord(const Pose2D& p) { return {p.x, p.y}; }
///
/// Converts a coordinate to a pose with the option to set the pose's heading
///
/// @param c the coordinate to convert to a pose
/// @param theta optional heading for the returned pose
/// @return the coordinate as a pose
///
inline constexpr Pose2D to_pose(const Coordinate& c, Angle theta = 0_deg)
{
    return {c.x, c.y, theta};
}

///
/// Translates a relative coordinate point into an absolute coordinate point
/// given the frame of reference.
///
/// @param relative_point coordinate describing the relative point
/// @param frame the frame of reference
/// @return  coordinate in the absolute frame of reference
///
Coordinate to_abs_coord(const Coordinate& relative_point, const Pose2D& frame);
///
/// Translates an absolute coordinate point back into a relative coordinate
/// point given the frame of reference
///
/// @param abs_point coordinate describing the absolute point
/// @param frame the frame of reference
/// @return  coordinate in the relative frame of reference
///
Coordinate to_rel_coord(const Coordinate& abs_point, const Pose2D& frame);
///
/// Converts a relative angle to an absolute heading w.r.t. the global frame
///
/// @param relative the
/// @param frame
/// @return Angle
///
Angle to_abs_heading(Angle relative, const Pose2D& frame);

///
/// Calculates the distance between a and b, always positive.
///
/// @param a the position at a
/// @param b the position at b
/// @param[out] dx the x-component of the distance
/// @param[out] dy the y-component of the distance
///
/// @return the distance between a and b, always positive.
///
Length distance(const Coordinate& a,
                const Coordinate& b,
                units::Length*    dx = nullptr,
                units::Length*    dy = nullptr);
}  // namespace units
}  // namespace bte
