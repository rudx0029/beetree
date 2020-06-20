#pragma once

#include "beetree/units/internal/fixed-pt-math.hpp"
#include "beetree/units/internal/fixed-pt.hpp"
#include "beetree/units/internal/floating-pt-math.hpp"
#include "beetree/units/internal/floating-pt.hpp"

namespace bte {
namespace units_internal {
///
/// The platform's 'Real' type as 64-bit fixed point Q32.32
///
// using Real = core::FixedPt</*fractional bits*/ 21>;
// using RealMath = core::FixedPtMath<Real>;

///
/// The platform's 'Real' type as 32-bit floating point
///
using Real     = FloatingPt;
using RealMath = FloatingPtMath;

}  // namespace units_internal
}  // namespace bte