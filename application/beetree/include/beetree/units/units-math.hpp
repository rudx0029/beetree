//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

// NOTE: This file is dependent on being included at the end of units/units.hpp

namespace bte {
namespace units {
// trigonometric functions - angle quantities
template <class Q>
inline constexpr Unit<Q> abs(const Unit<Q>& a)
{
    return ops::abs(a);
}

// todo: figure out how to handle units for square and square roots
template <class Q>
inline Unit<Q> sqrt(const Unit<Q>& a)
{
    return ops::sqrt(a);
}
inline Scalar rand(void) { return cast<Scalar>(ops::rand<Scalar>()); }
inline Length sqrt(const Area& a) { return cast<Length>(ops::sqrt(a)); }
inline Scalar sin(const Angle& a) { return ops::sin(a); }
inline Scalar cos(const Angle& a) { return ops::cos(a); }
template <class Q>
inline Angle atan2(const Unit<Q>& y, const Unit<Q>& x)
{
    return ops::atan2(y, x);
}

///
/// Bounds an angle between -pi and pi using a recursive strategy. Use this
/// method when wanting to bound an angle during compile time.
///
/// @param angle the angle to bound
/// @return the angle bounded between -pi and pi
///
constexpr Angle bound_recursive(const Angle& angle) { return ops::bound_angle_recursive(angle); }

///
/// Bounds an angle between -pi and pi. Use this method when wanting to
/// bound an angle during run time.
///
/// @param angle the angle to bound
/// @return the angle bounded between -pi and pi
///
inline Angle bound(const Angle& angle) { return ops::bound_angle(angle); }
}  // namespace units
}  // namespace bte