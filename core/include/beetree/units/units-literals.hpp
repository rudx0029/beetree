//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

namespace bte {
namespace units {
namespace literals {

// NOTE: This file is dependent on being included at the end of units/units.hpp

// Unit Literals - Scalar
inline constexpr Scalar operator"" _scl(unsigned long long value)
{
    return make<scl>(static_cast<int32_t>(value));
}
inline constexpr Scalar operator"" _mscl(unsigned long long value)
{
    return make<mscl>(static_cast<int32_t>(value));
}
inline constexpr Scalar operator"" _uscl(unsigned long long value)
{
    return make<uscl>(static_cast<int32_t>(value));
}
// Unit Literals - Length
inline constexpr Length operator"" _m(unsigned long long value)
{
    return make<m>(static_cast<int32_t>(value));
}
inline constexpr Length operator"" _mm(unsigned long long value)
{
    return make<mm>(static_cast<int32_t>(value));
}
inline constexpr Length operator"" _um(unsigned long long value)
{
    return make<um>(static_cast<int32_t>(value));
}
// Unit Literals - Velocity
inline constexpr Velocity operator"" _mps(unsigned long long value)
{
    return make<mps>(static_cast<int32_t>(value));
}
inline constexpr Velocity operator"" _mmps(unsigned long long value)
{
    return make<mmps>(static_cast<int32_t>(value));
}
inline constexpr Velocity operator"" _umps(unsigned long long value)
{
    return make<umps>(static_cast<int32_t>(value));
}
// Unit Literals - Accel
inline constexpr Accel operator"" _mpss(unsigned long long value)
{
    return make<mpss>(static_cast<int32_t>(value));
}
inline constexpr Accel operator"" _mmpss(unsigned long long value)
{
    return make<mmpss>(static_cast<int32_t>(value));
}
// Unit Literals - Angle
inline constexpr Angle operator"" _rad(unsigned long long value)
{
    return make<rad>(static_cast<int32_t>(value));
}
inline constexpr Angle operator"" _mrad(unsigned long long value)
{
    return make<mrad>(static_cast<int32_t>(value));
}
inline constexpr Angle operator"" _urad(unsigned long long value)
{
    return make<urad>(static_cast<int32_t>(value));
}
inline constexpr Angle operator"" _deg(unsigned long long value)
{
    return make<deg>(static_cast<int32_t>(value));
}
inline constexpr Angle operator"" _mdeg(unsigned long long value)
{
    return make<mdeg>(static_cast<int32_t>(value));
}
// Unit Literals - Angular Velocity
inline constexpr AngVelocity operator"" _radps(unsigned long long value)
{
    return make<radps>(static_cast<int32_t>(value));
}
inline constexpr AngVelocity operator"" _mradps(unsigned long long value)
{
    return make<mradps>(static_cast<int32_t>(value));
}
inline constexpr AngVelocity operator"" _rps(unsigned long long value)
{
    return make<rps>(static_cast<int32_t>(value));
}
inline constexpr AngVelocity operator"" _mrps(unsigned long long value)
{
    return make<mrps>(static_cast<int32_t>(value));
}
// Unit Literals - Angular Acceleration
inline constexpr AngAccel operator"" _radpss(unsigned long long value)
{
    return make<radpss>(static_cast<int32_t>(value));
}
inline constexpr AngAccel operator"" _mradpss(unsigned long long value)
{
    return make<mradpss>(static_cast<int32_t>(value));
}
inline constexpr AngAccel operator"" _rpss(unsigned long long value)
{
    return make<rpss>(static_cast<int32_t>(value));
}
inline constexpr AngAccel operator"" _mrpss(unsigned long long value)
{
    return make<mrpss>(static_cast<int32_t>(value));
}

// Unit Literals - Time - Native
inline constexpr Time operator"" _sec(unsigned long long value)
{
    return make<sec>(static_cast<int32_t>(value));
}
inline constexpr Time operator"" _msec(unsigned long long value)
{
    return make<msec>(static_cast<int32_t>(value));
}

// Unit Literals - Area
inline constexpr Area operator"" _sqm(unsigned long long value)
{
    return make<sqm>(static_cast<int32_t>(value));
}
inline constexpr Area operator"" _sqmm(unsigned long long value)
{
    return make<sqmm>(static_cast<int32_t>(value));
}

}  // namespace literals
}  // namespace units
}  // namespace bte