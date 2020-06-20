//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

namespace bte {
namespace units_internal {
template <class R>
struct FixedPtMath
{
    static constexpr R zero() { return R::from_int(0); }
    static constexpr R half() { return R::from_int(1) / R::from_int(2); }
    static constexpr R one() { return R::from_int(1); }
    static constexpr R two() { return R::from_int(2); }

    ///
    /// Absolute Value
    /// @return the absolute value of `a`
    ///
    static constexpr R abs(const R& a) { return a < zero() ? -a : a; }

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
    static R bound_angle(const R& a)
    {
        R x = a;
        while (x > R::pi())
        {
            x = x - two() * R::pi();
        }

        while (x < -R::pi())
        {
            x = x + two() * R::pi();
        }

        return x;
    }

    ///
    /// Sin
    ///
    /// @param a
    /// @return the result of the sin function
    ///
    static R sin(const R& a)
    {
        R x = bound_angle(a);
        if (x > R::pi_2())
        {
            return -approx_sin(x - R::pi());
        }
        if (x < -R::pi_2())
        {
            return -approx_sin(x + R::pi());
        }
        return approx_sin(x);
    }

    ///
    /// Cos
    ///
    /// @param x
    /// @return the result of the cos function
    ///
    static R cos(const R& x) { return sin(R::pi_2() - x); }

    static R atan2(const R& y, const R& x)
    {
        constexpr R k = R::from_float(0.28125);

        R        q_abs    = abs(y);
        R        i_abs    = abs(x);
        bool     q_is_pos = (y >= zero());
        bool     i_is_pos = (x >= zero());
        const R& q        = y;
        const R& i        = x;
        R        q_2      = q * q;
        R        i_2      = i * i;
        R        theta;

        if (q == zero() && i == zero())
        {
            theta = zero();
        }
        else if (i_is_pos && i_abs >= q_abs)  // quadrants 1 & 8 or -45deg to 45 deg
        {
            theta = (i * q) / (i_2 + k * q_2);
        }
        else if (q_is_pos && q_abs > i_abs)  // quadrants 2 & 3 or 45 deg to 135 deg
        {
            theta = R::pi_2() - ((i * q) / (q_2 + k * i_2));
        }
        else if (!q_is_pos && q_abs > i_abs)  // quadrants 6 & 7 or -135 deg to -45 deg
        {
            theta = -R::pi_2() - ((i * q) / (q_2 + k * i_2));
        }
        else if (!i_is_pos && i_abs >= q_abs)  // quadrant 4 & 5 or 135 to -135 deg
        {
            theta = R::pi() + ((i * q) / (i_2 + k * q_2));
            theta = bound_angle(theta);
        }
        else
        {
            theta = zero();
        }

        return theta;
    }

    static R sqrt(const R& a)
    {
        if (a < zero())
        {
            return -one();
        }
        if (a == zero() || a == one())
        {
            return a;
        }
        if (a < one())
        {
            return one() / sqrt(one() / a);
        }

        // We'll base the newton/babalonian method based on the the
        // of bits the value occupies.
        typename R::type v   = a.value;
        R                x_n = a;  // initial guess
        while (v > 0)
        {
            x_n = (x_n + (a / x_n)) * half();
            v   = v >> 1;
        }

        return x_n;
    }

private:
    static R approx_sin(const R& x)
    {
        constexpr R ifact_3 = R::from_float(1.0 / (3.0 * 2.0));
        constexpr R ifact_5 = R::from_float(1.0 / (5.0 * 4.0 * 3.0 * 2.0));
        constexpr R ifact_7 = R::from_float(1.0 / (7.0 * 6.0 * 5.0 * 4.0 * 3.0 * 2.0));
        // constexpr R ifact_9 = R::from_float(1.0 / (9.0 * 8.0 * 7.0 * 6.0 * 5.0 * 4.0 * 3.0
        // * 2.0)); constexpr R ifact_11 = R::from_float(1.0 / (11.0 * 10.0 * 9.0 * 8.0 * 7.0 * 6.0
        // * 5.0 * 4.0 * 3.0
        // * 2.0));

        // taylor series approximation
        // sin(x) = x - x^3/3! + x^5/5! - x^7/7!

        R x3 = x * x * x;
        R x5 = x3 * x * x;
        R x7 = x5 * x * x;
        // R x9 = x7*x*x;
        // R x11 = x9*x*x;

        return x - x3 * ifact_3 + x5 * ifact_5 - x7 * ifact_7
            // + x9*ifact_9
            // - x11*ifact_11;
            ;
    }
};
}  // namespace units_internal
}  // namespace bte