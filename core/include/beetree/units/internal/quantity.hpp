//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

namespace bte {
namespace units_internal {
///
/// Physical quantity types. This forms the basis of a Unit<Q> where Q
/// is this type, e.g. Unit<quantity::Length> is the unit for length.
///
struct Quantities
{
    // create a specific type for each unit. (instead of an enum)
    struct Scalar
    {};
    struct Length
    {};
    struct Velocity
    {};
    struct Acceleration
    {};
    struct Angle
    {};
    struct AngularVelocity
    {};
    struct AngularAcceleration
    {};
    struct Area
    {};
    struct Time
    {};
};
}  // namespace units_internal
}  // namespace bte