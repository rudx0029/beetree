//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/units/internal/floating-pt-math.hpp"
#include <cstdlib>

namespace bte {
namespace units_internal {
using R = FloatingPt;

//
// the rand implemented in std::rand was depricated for another heavier (and
// non-existent) function. This was from a series of searches in the web. I
// posited the random seed prime numbers as seeds of prime numbers seemed to be
// a more solid approach for better randomness.
//
static constexpr int A = 306703;   // any number in (0, RAND_MAX) - prime
static constexpr int C = 1299257;  // any number in [0, RAND_MAX) - prime

static uint32_t b_rand()
{
    static uint64_t prev = 109;  // seed. any number in [0, RAND_MAX) - use
                                 // prime
    prev = (prev * A + C) % RAND_MAX;
    return static_cast<uint32_t>(prev);
}

R FloatingPtMath::rand(void)
{
    R r;
    R max;

    //
    // since "std::rand() / RAND_MAX" consistently results in 0 given the nature
    // of integer division It seemed more appropriate to move the numbers into
    // float to get this to work.
    //
    return r.from_int(b_rand()) / max.from_int(RAND_MAX);
}

///
/// Bounds an angle between -pi and pi. This method is intended for
/// run-time calculations.
///
/// @param a
/// @return R
///
R FloatingPtMath::bound_angle(const R& a)
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

static R approx_sin(const R& x)
{
    constexpr R ifact_3 = R::from_float(1.0 / (3.0 * 2.0));
    constexpr R ifact_5 = R::from_float(1.0 / (5.0 * 4.0 * 3.0 * 2.0));
    constexpr R ifact_7 = R::from_float(1.0 / (7.0 * 6.0 * 5.0 * 4.0 * 3.0 * 2.0));
    // constexpr R ifact_9 = R::from_float(1.0 / (9.0 * 8.0 * 7.0 * 6.0 * 5.0
    // * 4.0 * 3.0 * 2.0)); constexpr R ifact_11 = R::from_float(1.0 / (11.0
    // * 10.0 * 9.0 * 8.0 * 7.0 * 6.0 * 5.0 * 4.0 * 3.0
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

///
/// Sin
///
/// @param a
/// @return the result of the sin function
///
R FloatingPtMath::sin(const R& a)
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
R FloatingPtMath::cos(const R& x) { return sin(R::pi_2() - x); }

R FloatingPtMath::atan2(const R& y, const R& x)
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

// Directly copied from :
// https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
R FloatingPtMath::sqrt(const R& a)
{
    union
    {
        int   i;
        float x;
    } u;
    u.x = a.value;
    u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

    // Two Babylonian Steps (simplified from:)
    // u.x = 0.5f * (u.x + x/u.x);
    // u.x = 0.5f * (u.x + x/u.x);
    u.x = u.x + a.value / u.x;
    u.x = 0.25f * u.x + a.value / u.x;

    return {u.x};
}
}  // namespace units_internal
}  // namespace bte