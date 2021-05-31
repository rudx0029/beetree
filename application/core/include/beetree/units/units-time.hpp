//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

// NOTE: This file is dependent on being included at the end of units/units.hpp

#include "beetree/btos/clock.hpp"

namespace bte {
namespace units {
inline constexpr Time cast(const bte::Clock::ms& from) { return make<msec>(from.count()); }

template <>
inline constexpr bte::Clock::ms cast<bte::Clock::ms, Time>(const Time& from)
{
    return bte::Clock::ms{as<msec>(from)};
}

inline constexpr bte::Clock::ms abs(bte::Clock::ms d) { return d >= bte::Clock::ms{0} ? d : -d; }

// Accel = Velocity / Time
inline constexpr Accel operator/(const Velocity& d, const bte::Clock::ms& t)
{
    return ops::div<quantity::Acceleration>(d, make<mscl>(static_cast<int32_t>(t.count())));
}

// Length = Velocity *  Time

inline constexpr Length operator*(const Velocity& d, const bte::Clock::ms& t)
{
    return ops::mul<quantity::Length>(d, make<mscl>(static_cast<int32_t>(t.count())));
}

inline constexpr Length operator*(const bte::Clock::ms& t, const Velocity& v)
{
    return ops::mul<quantity::Length>(make<mscl>(static_cast<int32_t>(t.count())), v);
}

// AngVelocity = AngAccel *  Time
inline constexpr AngVelocity operator*(const AngAccel& d, const bte::Clock::ms& t)
{
    return ops::mul<quantity::AngularVelocity>(d, make<mscl>(static_cast<int32_t>(t.count())));
}

// AngVelocity = Time * AngAccel
inline constexpr AngVelocity operator*(const bte::Clock::ms& t, const AngAccel& d)
{
    return ops::mul<quantity::AngularVelocity>(d, make<mscl>(static_cast<int32_t>(t.count())));
}

// Angle = AngVelocity *  Time
inline constexpr Angle operator*(const AngVelocity& d, const bte::Clock::ms& t)
{
    return ops::mul<quantity::Angle>(d, make<mscl>(static_cast<int32_t>(t.count())));
}

// Angle = Time * AngVelocity
inline constexpr Angle operator*(const bte::Clock::ms& t, const AngVelocity& d)
{
    return ops::mul<quantity::Angle>(d, make<mscl>(static_cast<int32_t>(t.count())));
}

inline constexpr AngVelocity operator/(const Angle& a, const bte::Clock::ms& t)
{
    return ops::div<quantity::AngularVelocity>(a, make<mscl>(static_cast<int32_t>(t.count())));
}

inline constexpr AngAccel operator/(const AngVelocity& w, const bte::Clock::ms& t)
{
    return ops::div<quantity::AngularAcceleration>(w, make<mscl>(static_cast<int32_t>(t.count())));
}

///
/// Division operator overload for calculation velocity from length and time
///
/// @param d the length
/// @param t the time duration
/// @return the quantity Velocity
///
inline constexpr Velocity operator/(const Length& d, const bte::Clock::ms& t)
{
    return ops::div<quantity::Velocity>(d, make<mscl>(static_cast<int32_t>(t.count())));
}

}  // namespace units
}  // namespace bte

// Unit Literals - Time - Platform interface
inline constexpr bte::Clock::ms operator"" _s(unsigned long long value)
{
    return bte::Clock::milliseconds{1000 * static_cast<int32_t>(value)};
}
inline constexpr bte::Clock::ms operator"" _ms(unsigned long long value)
{
    return bte::Clock::milliseconds{static_cast<int32_t>(value)};
}