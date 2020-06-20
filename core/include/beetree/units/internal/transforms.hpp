//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include <cmath>
#include <cstdint>
#include "beetree/units/internal/real.hpp"

namespace bte {
namespace units_internal {

///
/// When converting from a Unit<Q> to integer, transforms are used to
/// translate between units. For instance, an angle can be represented
/// in both degrees in radians. Under the hood, per se, we store the angle
/// as a measurement of radians. The transform allows the angle to be
/// expressed in degrees but converts it to radians for storage in the
/// Unit<Q>.
///
struct Transforms
{
    struct Identity
    {
        inline static constexpr Real to_quantity(Real r) { return r; }
        inline static constexpr Real from_quantity(Real r) { return r; }
    };

    struct DegToRad
    {
        inline static constexpr Real to_quantity(Real r)
        {
            return r * Real::pi() / Real::from_int(180);
        }
        inline static constexpr Real from_quantity(Real r)
        {
            return r * Real::from_int(180) / Real::pi();
        }
    };
};
}  // namespace units_internal
}  // namespace bte