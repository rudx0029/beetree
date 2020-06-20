//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

// NOTE: This file is dependent on being included at the end of units/units.hpp

#include <type_traits>

namespace bte {
namespace units_internal {

using ops         = OperationsFriend;
using quantity    = units_internal::Quantities;
using Scalar      = Unit<quantity::Scalar>;
using Length      = Unit<quantity::Length>;
using Position    = Unit<quantity::Length>;
using Radius      = Unit<quantity::Length>;
using Velocity    = Unit<quantity::Velocity>;
using Accel       = Unit<quantity::Acceleration>;
using Angle       = Unit<quantity::Angle>;
using AngVelocity = Unit<quantity::AngularVelocity>;
using AngAccel    = Unit<quantity::AngularAcceleration>;
using Area        = Unit<quantity::Area>;
using Time        = Unit<quantity::Time>;

// basic math operations
template <class Q>
inline constexpr Unit<Q> operator-(const Unit<Q>& a)
{
    return ops::neg(a);
}
template <class Q>
inline constexpr Unit<Q> operator+(const Unit<Q>& a, const Unit<Q>& b)
{
    return ops::add(a, b);
}
template <class Q>
inline constexpr Unit<Q> operator-(const Unit<Q>& a, const Unit<Q>& b)
{
    return ops::sub(a, b);
}
template <class Q>
inline constexpr Scalar operator/(const Unit<Q>& a, const Unit<Q>& b)
{
    return ops::div<quantity::Scalar>(a, b);
}
template <class Q>
inline void operator+=(Unit<Q>& a, const Unit<Q>& b)
{
    a = ops::add(a, b);
}
template <class Q>
inline void operator-=(Unit<Q>& a, const Unit<Q>& b)
{
    a = ops::sub(a, b);
}

// comparison
template <class Q>
inline constexpr bool operator==(const Unit<Q>& a, const Unit<Q>& b)
{
    return OperationsFriend::eq(a, b);
}
template <class Q>
inline constexpr bool operator!=(const Unit<Q>& a, const Unit<Q>& b)
{
    return !ops::eq(a, b);
}
template <class Q>
inline constexpr bool operator>(const Unit<Q>& a, const Unit<Q>& b)
{
    return ops::gt(a, b);
}
template <class Q>
inline constexpr bool operator>=(const Unit<Q>& a, const Unit<Q>& b)
{
    return ops::gte(a, b);
}
template <class Q>
inline constexpr bool operator<(const Unit<Q>& a, const Unit<Q>& b)
{
    return ops::lt(a, b);
}
template <class Q>
inline constexpr bool operator<=(const Unit<Q>& a, const Unit<Q>& b)
{
    return ops::lte(a, b);
}

///
/// Scalar Multiplication
///
/// @param a Scalar quantity
/// @param b Scalr quantity
/// @return product of a and b as a Scalar
///
inline constexpr Scalar operator*(const Scalar& a, const Scalar& b)
{
    return ops::mul<quantity::Scalar>(a, b);
}
///
/// Scalar Division
///
/// @param a Scalar quantity
/// @param b Scalar quantity
/// @return dividend of a over b as a Scalar
///
inline constexpr Scalar operator/(const Scalar& a, const Scalar& b)
{
    return ops::div<quantity::Scalar>(a, b);
}
///
/// Quantity - Scalar Multiplication
///
/// @param a Quantity
/// @param b Scalar quantity
/// @return product of a and b as the Quantity
///
template <class Q,
          typename = typename std::enable_if<!std::is_same<Q, quantity::Scalar>::value>::type>
inline constexpr Unit<Q> operator*(const Unit<Q>& a, const Scalar& b)
{
    return ops::mul<Q>(a, b);
}
///
/// Quantity - Scalar Multiplication
///
/// @param a Scalar quantity
/// @param b Quantity
/// @return product of a and b as the Quantity
///
template <class Q,
          typename = typename std::enable_if<!std::is_same<Q, quantity::Scalar>::value>::type>
inline constexpr Unit<Q> operator*(const Scalar& a, const Unit<Q>& b)
{
    return ops::mul<Q>(b, a);
}
///
/// Quantity - Scalar Division
///
/// @param a Quantity
/// @param b Scalar quantity
/// @return dividend of the quantity over the scalar as a Quantity
///
template <class Q,
          typename = typename std::enable_if<!std::is_same<Q, quantity::Scalar>::value>::type>
inline constexpr Unit<Q> operator/(const Unit<Q>& a, const Scalar& b)
{
    return ops::div<Q>(a, b);
}
///
/// Scalar - Quantity Division
///
/// @param a Scalar quantity
/// @param b Quantity
/// @return dividend of the scalar over the quantity as a Quantity
///
template <class Q,
          typename = typename std::enable_if<!std::is_same<Q, quantity::Scalar>::value>::type>
inline constexpr Unit<Q> operator/(const Scalar& a, const Unit<Q>& b)
{
    return ops::div<Q>(a, b);
}

///
/// Division operator overload for calculation velocity from length and time
///
/// @param d the length
/// @param t the time duration
/// @return the quantity Velocity
///
inline constexpr Velocity operator/(const Length& d, const Time& t)
{
    return ops::div<quantity::Velocity>(d, t);
}

// Accel = Velocity / Time
inline constexpr Accel operator/(const Velocity& v, const Time& t)
{
    return ops::div<quantity::Acceleration>(v, t);
}

// Length = Velocity *  Time
inline constexpr Length operator*(const Velocity& d, const Time& t)
{
    return ops::mul<quantity::Length>(d, t);
}

// Length = Time * Velocity
inline constexpr Length operator*(const Time& t, const Velocity& v)
{
    return ops::mul<quantity::Length>(t, v);
}

// AngVelocity = AngAccel *  Time
inline constexpr AngVelocity operator*(const AngAccel& d, Time& t)
{
    return ops::mul<quantity::AngularVelocity>(d, t);
}

// AngVelocity = Time * AngAccel
inline constexpr AngVelocity operator*(const Time& t, const AngAccel& d)
{
    return ops::mul<quantity::AngularVelocity>(d, t);
}

// Angle = AngVelocity *  Time
inline constexpr Angle operator*(const AngVelocity& d, const Time& t)
{
    return ops::mul<quantity::Angle>(d, t);
}

// Angle = Time * AngVelocity
inline constexpr Angle operator*(const Time& t, const AngVelocity& d)
{
    return ops::mul<quantity::Angle>(d, t);
}
inline constexpr AngVelocity operator/(const Angle& a, const Time& t)
{
    return ops::div<quantity::AngularVelocity>(a, t);
}

inline constexpr AngAccel operator/(const AngVelocity& w, const Time& t)
{
    return ops::div<quantity::AngularAcceleration>(w, t);
}

// Velocity = Radius * AngVelocity
inline constexpr Velocity operator*(const Length& radius, const AngVelocity& w)
{
    return ops::mul<quantity::Velocity>(radius, w);
}

// Velocity = AngVelocity * Radius
inline constexpr Velocity operator*(const AngVelocity& w, const Length& radius)
{
    return radius * w;
}

// AngVelocity = Velocity / Radius
inline constexpr AngVelocity operator/(const Velocity& v, const Length& radius)
{
    return ops::div<quantity::AngularVelocity>(v, radius);
}

// AngAccel = Accel / Radius
inline constexpr AngAccel operator/(const Accel& v, const Length& radius)
{
    return ops::div<quantity::AngularAcceleration>(v, radius);
}

inline constexpr Area operator*(const Length& a, const Length& b)
{
    return ops::mul<quantity::Area>(a, b);
}
inline constexpr Length operator/(const Area& a, const Length& b)
{
    return ops::div<quantity::Length>(a, b);
}
}  // namespace units_internal
}  // namespace bte