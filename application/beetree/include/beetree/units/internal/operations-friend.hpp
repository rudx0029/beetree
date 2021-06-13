//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/units/internal/unit.hpp"

namespace bte {
namespace units_internal {
class OperationsFriend
{
public:
    // integer conversion
    template <class Q, class TRatio, class TTransform = Transforms::Identity>
    inline static constexpr Unit<Q> make(int32_t value)
    {
        return TTransform::to_quantity(Real::from_int(value) * Real::from_int(TRatio::num) /
                                       Real::from_int(TRatio::den));
    }

    template <class Q, class TRatio, class TTransform = Transforms::Identity>
    inline static constexpr int32_t as(const Unit<Q>& v)
    {
        return Real::to_int(TTransform::from_quantity(v.m_value) * Real::from_int(TRatio::den) /
                            Real::from_int(TRatio::num));
    }

    // basic math operations
    template <class Q>
    inline static constexpr Unit<Q> neg(const Unit<Q>& a)
    {
        return {-a.m_value};
    }

    template <class Q>
    inline static constexpr Unit<Q> add(const Unit<Q>& a, const Unit<Q>& b)
    {
        return {a.m_value + b.m_value};
    }

    template <class Q>
    inline static constexpr Unit<Q> sub(const Unit<Q>& a, const Unit<Q>& b)
    {
        return {a.m_value - b.m_value};
    }

    template <class Q, class L, class J>
    inline static constexpr Unit<Q> mul(const Unit<L>& a, const Unit<J>& b)
    {
        return {a.m_value * b.m_value};
    }

    template <class Q, class L, class J>
    inline static constexpr Unit<Q> div(const Unit<L>& a, const Unit<J>& b)
    {
        return {a.m_value / b.m_value};
    }

    // comparison
    template <class Q>
    inline static constexpr bool eq(const Unit<Q>& a, const Unit<Q>& b)
    {
        return a.m_value == b.m_value;
    }

    template <class Q>
    inline static constexpr bool lt(const Unit<Q>& a, const Unit<Q>& b)
    {
        return a.m_value < b.m_value;
    }

    template <class Q>
    inline static constexpr bool lte(const Unit<Q>& a, const Unit<Q>& b)
    {
        return a.m_value <= b.m_value;
    }

    template <class Q>
    inline static constexpr bool gt(const Unit<Q>& a, const Unit<Q>& b)
    {
        return a.m_value > b.m_value;
    }

    template <class Q>
    inline static constexpr bool gte(const Unit<Q>& a, const Unit<Q>& b)
    {
        return a.m_value >= b.m_value;
    }

    // values
    template <class Q>
    inline static constexpr Unit<Q> epsilon()
    {
        return {Real::epsilon()};
    }

    template <class Q>
    inline static constexpr Unit<Q> infinity()
    {
        return {Real::infinity()};
    }

    template <class Q>
    inline static constexpr Unit<Q> max()
    {
        return {Real::max()};
    }

    template <class Q>
    inline static constexpr Unit<Q> min()
    {
        return {Real::min()};
    }

    template <class Q>
    inline static constexpr Unit<Q> pi()
    {
        return {Real::pi()};
    }

    template <class Q>
    inline static constexpr Unit<Q> pi_2()
    {
        return {Real::pi_2()};
    }

    template <class Q>
    inline static constexpr Unit<Q> bound_angle_recursive(const Unit<Q>& x)
    {
        return {RealMath::bound_angle_recursive(x.m_value)};
    }

    template <class Q>
    inline static Unit<Q> bound_angle(const Unit<Q>& x)
    {
        return {RealMath::bound_angle(x.m_value)};
    }

    // cast
    template <class Q, class QCast>
    inline static constexpr Unit<QCast> cast(const Unit<Q>& v)
    {
        return {v.m_value};
    }

    // non-linear

    template <class Q>
    inline static constexpr Unit<Q> rand(void)
    {
        return {RealMath::rand()};
    }

    template <class Q>
    inline static constexpr Unit<Q> abs(const Unit<Q>& a)
    {
        return {RealMath::abs(a.m_value)};
    }

    template <class Q>
    inline static Unit<Q> sqrt(const Unit<Q>& a)
    {
        return {RealMath::sqrt(a.m_value)};
    }

    // trigonometric functions
    inline static Unit<Quantities::Scalar> sin(const Unit<Quantities::Angle>& a)
    {
        return {RealMath::sin(a.m_value)};
    }
    inline static Unit<Quantities::Scalar> cos(const Unit<Quantities::Angle>& a)
    {
        return {RealMath::cos(a.m_value)};
    }
    template <class Q>
    inline static Unit<Quantities::Angle> atan2(const Unit<Q>& y, const Unit<Q>& x)
    {
        return {RealMath::atan2(y.m_value, x.m_value)};
    }
};
}  // namespace units_internal
}  // namespace bte