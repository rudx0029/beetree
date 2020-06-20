//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <cstdint>
#include <limits>

namespace bte {
namespace units_internal {
///
/// 32-bit Fixed Point Real Number Template where `N` is the number of
/// fractional bits. It follows the format of QI.N where I is the number of
/// integer bits including the sign bit.
///
/// @tparam N The number of fractional bits in the fixed point representation
///
template <int32_t N>
struct FixedPt
{
    using type  = int32_t;  ///< underlying signed integer type for FixedPt<>, e.g. int32_t
    using dtype = int64_t;  ///< underlying double signed integer type for mul/div, e.g. int64_t
    type value;             ///< Storage for the fixed point number

public:
    ///
    /// Converts a floating point number to fixed point representation
    ///
    /// > NOTE: This should only be called at compile time to create
    /// > constant expressions in order to not include the floating point
    /// > run time libraries
    ///
    /// @param f the floating point number to convert
    /// @return the fixed point representation
    ///
    static constexpr FixedPt<N> from_float(float f)
    {
        return {static_cast<type>(f * ((1 << N) + 0.5f))};
    }

    static constexpr float to_float(const FixedPt<N>& real)
    {
        return static_cast<float>(real.value) / ((1 << N) + 0.5f);
    }

    ///
    /// Converts a fixed point real number to its integer representation,
    /// dropping its fractional part.
    ///
    /// @param real the fixed point number to convert to an int
    /// @return the integer representation minus its fractional part.
    ///
    static constexpr int32_t to_int(const FixedPt<N>& real) { return real.value >> N; }

    ///
    /// Converts an integer to its fixed point real number representation.
    ///
    /// @param i the integer to convert to fixed point representation
    /// @return the fixed point representation
    ///
    static constexpr FixedPt<N> from_int(int32_t i) { return {i << N}; }

    ///
    /// @return PI Constant
    ///
    static constexpr FixedPt<N> pi() { return {from_float(3.14159265358979323846)}; }
    ///
    /// @return PI / 2 Constant
    ///
    static constexpr FixedPt<N> pi_2() { return {from_float(3.14159265358979323846 / 2.0)}; }
    ///
    /// @return Epsilon Constant - smallest magnitude
    ///
    static constexpr FixedPt<N> epsilon() { return {1}; }
    ///
    /// @return < Max Constant
    ///
    static constexpr FixedPt<N> max() { return {std::numeric_limits<type>::max()}; }
    ///
    /// @return Min Constant
    ///
    static constexpr FixedPt<N> min() { return {std::numeric_limits<type>::min()}; }
    ///
    /// @return Infinity Constant - largest magnitude
    ///
    static constexpr FixedPt<N> infinity() { return {std::numeric_limits<type>::max()}; }
};

///
/// Negative operator
///
/// @tparam N The number of fractional bits in the fixed point representation
/// @return The negative of `a`
///
template <int32_t N>
constexpr FixedPt<N> operator-(const FixedPt<N>& a)
{
    return {-a.value};
}
///
/// Addition operator
///
/// @tparam N The number of fractional bits in the fixed point representation
/// @return the sum of `a` and `b`.
///
template <int32_t N>
constexpr FixedPt<N> operator+(const FixedPt<N>& a, const FixedPt<N>& b)
{
    return {a.value + b.value};
}
///
/// Subtraction operator
///
/// @tparam N The number of fractional bits in the fixed point representation
/// @return the difference of `a` and `b`, e.g. `a - b`.
///
template <int32_t N>
constexpr FixedPt<N> operator-(const FixedPt<N>& a, const FixedPt<N>& b)
{
    return {a.value - b.value};
}

// using a constexpr class seems to save on flash than directly
// implementing in the function
template <int32_t N>
class FixedPtMultDiv
{
public:
    using type  = typename FixedPt<N>::type;
    using dtype = typename FixedPt<N>::dtype;
    static constexpr dtype scale() { return static_cast<dtype>(1) << N; }

    dtype a;
    dtype b;

    constexpr FixedPtMultDiv(const FixedPt<N>& x, const FixedPt<N>& y) : a(x.value), b(y.value) {}

    constexpr FixedPt<N> multiply() const { return {static_cast<type>((a * b) / scale())}; }

    constexpr FixedPt<N> divide() const { return {static_cast<type>((a * scale()) / b)}; }
};

///
/// Multiplication operator
///
/// @tparam N The number of fractional bits in the fixed point representation
/// @return the product of `a` and `b`, e.g. `a * b`.
///
template <int32_t N>
constexpr FixedPt<N> operator*(const FixedPt<N>& a, const FixedPt<N>& b)
{
    return FixedPtMultDiv<N>(a, b).multiply();
}

///
/// Division operator
///
/// @tparam N The number of fractional bits in the fixed point representation
/// @return the result of `a` divided by `b`, e.g. `a / b`.
///
template <int32_t N>
constexpr FixedPt<N> operator/(const FixedPt<N>& a, const FixedPt<N>& b)
{
    return FixedPtMultDiv<N>(a, b).divide();
}

///
/// Equality operator
///
/// @tparam N The number of fractional bits in the fixed point representation
/// @return true if a and b are identically equal
/// @return false otherwise
///
template <int32_t N>
constexpr bool operator==(const FixedPt<N>& a, const FixedPt<N>& b)
{
    return a.value == b.value;
}

///
/// Inequality operator
///
/// @tparam N The number of fractional bits in the fixed point representation
/// @return true if a and b are not equal
/// @return false otherwise
///
template <int32_t N>
constexpr bool operator!=(const FixedPt<N>& a, const FixedPt<N>& b)
{
    return a.value != b.value;
}

///
/// Greater-than operator
///
/// @tparam N The number of fractional bits in the fixed point representation
/// @return true if a is greater than b
/// @return false otherwise
///
template <int32_t N>
constexpr bool operator>(const FixedPt<N>& a, const FixedPt<N>& b)
{
    return a.value > b.value;
}

///
/// Greater-than Equal operator
///
/// @tparam N The number of fractional bits in the fixed point representation
/// @return true if a is greater than or equal to b
/// @return false otherwise
///
template <int32_t N>
constexpr bool operator>=(const FixedPt<N>& a, const FixedPt<N>& b)
{
    return a.value >= b.value;
}

///
/// Less-than operator
///
/// @tparam N The number of fractional bits in the fixed point representation
/// @return true if a is less than b
/// @return false otherwise
///
template <int32_t N>
constexpr bool operator<(const FixedPt<N>& a, const FixedPt<N>& b)
{
    return a.value < b.value;
}

///
/// Less-than Equal operator
///
/// @tparam N The number of fractional bits in the fixed point representation
/// @return true if a is less than or equal to b
/// @return false otherwise
///
template <int32_t N>
constexpr bool operator<=(const FixedPt<N>& a, const FixedPt<N>& b)
{
    return a.value <= b.value;
}

}  // namespace units_internal
}  // namespace bte