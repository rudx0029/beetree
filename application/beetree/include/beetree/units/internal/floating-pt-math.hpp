//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include <cmath>
#include "beetree/units/internal/floating-pt.hpp"

namespace bte {
namespace units_internal {
struct FloatingPtMath
{
    using R = FloatingPt;

    static constexpr R zero() { return R::from_float(0); }
    static constexpr R half() { return R::from_float(0.5); }
    static constexpr R one() { return R::from_float(1); }
    static constexpr R two() { return R::from_float(2); }

    ///
    /// Random number
    /// @return a random number between 0 and 1
    ///
    static R rand(void);

    ///
    /// Absolute Value
    /// @return the absolute value of `a`
    ///
    static constexpr R abs(const R& a) { return {a.value < 0 ? -a.value : a.value}; }

    ///
    /// @return the 'sign' of the given value, 1 if the value is greater
    /// than or equal to zero and -1 otherwise
    ///
    static constexpr R sign(const R& x) { return x < zero() ? -one() : one(); }

    ///
    /// Bounds an angle between -pi and pi using recursion. This method
    /// is intended for compile time and not run time
    ///
    /// @param x
    /// @return constexpr R
    ///
    static constexpr R bound_angle_recursive(const R& x)
    {
        return x > R::pi() ? bound_angle_recursive(x - two() * R::pi())
                           : x < -R::pi() ? bound_angle_recursive(x + two() * R::pi()) : x;
    }

    ///
    /// Bounds an angle between -pi and pi. This method is intended for
    /// run-time calculations.
    ///
    /// @param a
    /// @return R
    ///
    static R bound_angle(const R& a);

    ///
    /// Sin
    ///
    /// @param a
    /// @return the result of the sin function
    ///
    static R sin(const R& a);

    ///
    /// Cos
    ///
    /// @param x
    /// @return the result of the cos function
    ///
    static R cos(const R& x);

    static R atan2(const R& y, const R& x);

    static R sqrt(const R& a);
};
}  // namespace units_internal
}  // namespace bte