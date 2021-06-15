//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include <cmath>
#include <cstdint>
#include "beetree/units/internal/label.hpp"
#include "beetree/units/internal/quantity.hpp"
#include "beetree/units/internal/ratios.hpp"
#include "beetree/units/internal/real.hpp"
#include "beetree/units/internal/transforms.hpp"

namespace bte {
namespace units_internal {
///
/// The Unit! A template class providing storage for the specified quantity
/// `Q`. All operations are defined elsewhere.
///
/// @tparam Q the quantity, e.g. units::quantity::Length
///
template <class Q>
class Unit
{
public:
    constexpr Unit()            = default;
    constexpr Unit(const Unit&) = default;

    using quantity = Q;

    Unit(Unit&&) = default;
    ~Unit()      = default;

    Unit& operator=(const Unit&) = default;
    Unit& operator=(Unit&&) = default;

    // member access
    inline constexpr Real as_real() const { return m_value; }

private:
    template <class QFriend>
    friend class Unit;
    friend class OperationsFriend;

    constexpr Unit(const Real& f) : m_value(f) {}
    Real m_value = {0};
};  // namespace units_internaltemplate<classQ>classUnit
}  // namespace units_internal
}  // namespace bte