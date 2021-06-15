//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/units/internal/operations-friend.hpp"
#include "beetree/units/internal/unit.hpp"

namespace bte {
namespace units {
using ratios     = units_internal::Ratios;
using transforms = units_internal::Transforms;
using quantity   = units_internal::Quantities;
using ops        = units_internal::OperationsFriend;

template <class Q, class R, class T = transforms::Identity>
using Label = units_internal::Label<Q, R, T>;

template <class Q>
using Unit = units_internal::Unit<Q>;

// Quantities
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

// Global constants
constexpr Scalar PI   = ops::pi<quantity::Scalar>();
constexpr Scalar PI_2 = ops::pi_2<quantity::Scalar>();

// Label definitions for integer to quantity conversions
// see `make` and `as`
using scl    = Label<quantity::Scalar, ratios::identity>;  ///< dimension less for scalars
using m      = Label<quantity::Length, ratios::identity>;  ///< [m]eters
using rad    = Label<quantity::Angle, ratios::identity>;   ///< [rad]ians
using deg    = Label<quantity::Angle, ratios::identity,
                  transforms::DegToRad>;                  ///< [deg]rees
using mps    = Label<quantity::Velocity, ratios::identity>;  ///< [m]eters [p]er [s]econd
using mpss   = Label<quantity::Acceleration,
                   ratios::identity>;  ///< [m]eters [p]er [s]econd [s]econd
using radps  = Label<quantity::AngularVelocity,
                    ratios::identity>;  ///< [rad]ians [p]er [s]econd
using radpss = Label<quantity::AngularAcceleration,
                     ratios::identity>;  ///< [rad]ians [p]er [s]econd [p]er [s]econd
using rps    = Label<quantity::AngularVelocity,
                  ratios::identity>;  ///< [r]adians [p]er [s]econd
using rpss   = Label<quantity::AngularAcceleration,
                   ratios::identity>;  ///< [r]adians [p]er [s]econd [p]er [s]econd
using sqm    = Label<quantity::Area, ratios::identity>;  ///< [sq]uare [m]eters

using mscl    = Label<quantity::Scalar, ratios::milli>;  ///< [m]illi-dimension less
using mm      = Label<quantity::Length, ratios::milli>;  ///< [m]illi-[m]eters
using mrad    = Label<quantity::Angle, ratios::milli>;   ///< [m]illi-[rad]ians
using mdeg    = Label<quantity::Angle, ratios::milli,
                   transforms::DegToRad>;  ///< [deg]rees
using mmps    = Label<quantity::Velocity,
                   ratios::milli>;  ///< [m]illi-[m]eters [p]er [s]econd
using mmpss   = Label<quantity::Acceleration,
                    ratios::milli>;  ///< [m]illi-[m]eters [p]er [s]econd [s]econd
using mradps  = Label<quantity::AngularVelocity,
                     ratios::milli>;  ///< [m]illi-[rad]ians [p]er [s]econd
using mradpss = Label<quantity::AngularAcceleration,
                      ratios::milli>;  ///< [m]illi-[rad]ians [p]er [s]econd
                                       ///< [p]er [s]econd
using mrps  = Label<quantity::AngularVelocity,
                   ratios::milli>;  ///< [m]illi-[r]adians [p]er [s]econd
using mrpss = Label<quantity::AngularAcceleration,
                    ratios::milli>;                 ///< [m]illi-[r]adians [p]er [s]econd
                                                    ///< [p]er [s]econd
using sqmm = Label<quantity::Area, ratios::micro>;  ///< [sq]uare [m]illi-[m]eters

using uscl = Label<quantity::Scalar, ratios::micro>;    ///< micro-dimension less
using um   = Label<quantity::Length, ratios::micro>;    ///< micro-meters
using umps = Label<quantity::Velocity, ratios::micro>;  ///< micro-meters per second
using urad = Label<quantity::Angle, ratios::micro>;     ///< micro-radians

using msec = Label<quantity::Time, ratios::milli>;     ///< milli-seconds
using sec  = Label<quantity::Time, ratios::identity>;  ///< seconds

/**
 * @brief Converts a signed integer into a quantity, e.g. units::Length,
 * units::Velocity, etc., given the unit definition, e.g. units::m,
 * units::rad, units::mps
 *
 * /code
 * int32_t length_in_mm = 4000;
 * units::Length length_a = units::make<units::mm>(length_in_mm);
 *
 * int32_t length_in_m = 4;
 * units::Length length_b = units::make<units::m>(length_in_m);
 *
 * assert(length_a == length_b);
 * /endcode
 *
 * @tparam T the unit definition of the integer, units::m, units::rad,
 * units::mps, etc.
 * @tparam Q the quantity defined by the unit definition, defaults to
 * T::quantity
 * @tparam R the ratio defined by the unit definition, defaults to T::ratio
 * @tparam Tr the transform defined by the unit definition, defaults to
 * T::transform; typically transforms::Identity
 * @param value  the integer to convert
 * @return the quantity
 */
template <class T,
          class Q  = typename T::quantity,
          class R  = typename T::ratio,
          class Tr = typename T::transform>
inline constexpr Unit<Q> make(int32_t value)
{
    return ops::make<Q, R, Tr>(value);
}

/**
 * @brief Converts a quantiy, e.g. units::Length, units::Velocity, etc.,
 * into a signed integer in the ratio specified by the unit definition, e.g.
 * units::m, units::rad, units::mps
 *
 * /code
 * units::Length length_a = 4000_mm;
 * int32_t length_in_mm_a = units::as<units::mm>(length_a);
 *
 * units::Length length_b = 4500_mm;
 * int32_t length_in_m_b = units::as<units::m>(length_b);
 *
 * units::Length length_c = 3500_mm;
 * int32_t length_in_m_c = units::as<units::m>(length_c);
 *
 *
 * units::Length length_d = 4_m
 * int32_t length_in_m_d = units::as<units::m>(length_d);
 *
 * assert(length_in_mm_a == length_in_m_d * 1000);
 * assert(length_in_m_b != length_in_m_d); // length_in_m_b rounded to 5
 * assert(length_in_m_c == length_in_m_d); // length_in_m_c rounded to 4
 * /endcode
 *
 * @tparam T the unit definition of the integer, units::m, units::rad,
 * units::mps, etc.
 * @tparam Q the quantity defined by the unit definition, defaults to
 * T::quantity
 * @tparam R the ratio defined by the unit definition, defaults to T::ratio
 * @tparam Tr the transform defined by the unit definition, defaults to
 * T::transform; typically transforms::Identity
 * @param value  the integer to convert
 * @return the integer representation of the quantity in the specified units
 */
template <class T,
          class Q  = typename T::quantity,
          class R  = typename T::ratio,
          class Tr = typename T::transform>
inline constexpr int32_t as(const Unit<Q>& v)
{
    return ops::as<Q, R, Tr>(v);
}

/**
 * @brief Casts one quantity directly to the other without modifying the
 * underlying value.
 *
 * This should be used only when necessary.
 *
 * /code
 * units::Scalar s_before;
 * units::Scalar s_after;
 *
 * // cast a scalar to a length
 * units::Length l = units::cast<units::Length>(s_before);
 *
 * // cast back
 * s_after = units::cast<units::Scalar>(s_after);
 *
 * assert(s_before == s_after);
 * /endcode
 *
 * @tparam TTo The type of quantity to cast to
 * @tparam TFrom The type of quantity to cast from
 * @param from The quantity to cast
 * @return constexpr The casted quantity
 */
template <class TTo, class TFrom>
inline constexpr TTo cast(const TFrom& from)
{
    return ops::cast<typename TFrom::quantity, typename TTo::quantity>(from);
}

}  // namespace units
}  // namespace bte

#include "units-literals.hpp"
#include "units-math.hpp"
#include "units-operators.hpp"
#include "units-time.hpp"