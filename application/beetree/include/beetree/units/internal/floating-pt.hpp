//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <cmath>
#include <cstdint>
#include <limits>

namespace bte {
namespace units_internal {
///
/// 32-bit Floating Point Number
///
struct FloatingPt
{
    using type = float;  ///< underlying floating point type, e.g. float

    type value;  ///< Storage for the fixed point number

    // Integer to Fixed Point Conversion
    static constexpr int32_t to_int(const FloatingPt& real)
    {
        return static_cast<int32_t>(real.value);
    }
    static constexpr FloatingPt from_int(int32_t i) { return {static_cast<type>(i)}; }
    static constexpr FloatingPt from_float(type a) { return {a}; }
    static constexpr type       to_float(const FloatingPt& real) { return real.value; }
    // Constants
    static constexpr FloatingPt pi() { return {3.14159265358979323846f}; }
    static constexpr FloatingPt pi_2() { return {pi().value / 2.0f}; }
    static constexpr FloatingPt epsilon() { return {std::numeric_limits<type>::epsilon()}; }
    static constexpr FloatingPt infinity() { return {std::numeric_limits<type>::infinity()}; }
    static constexpr FloatingPt max() { return {std::numeric_limits<type>::max()}; }
    static constexpr FloatingPt min() { return {std::numeric_limits<type>::min()}; }
};

// Arithmetic
constexpr FloatingPt operator-(const FloatingPt& a);
constexpr FloatingPt operator+(const FloatingPt& a, const FloatingPt& b);
constexpr FloatingPt operator-(const FloatingPt& a, const FloatingPt& b);
constexpr FloatingPt operator*(const FloatingPt& a, const FloatingPt& b);
constexpr FloatingPt operator/(const FloatingPt& a, const FloatingPt& b);
// Comparison

constexpr bool operator==(const FloatingPt& a, const FloatingPt& b);

constexpr bool operator!=(const FloatingPt& a, const FloatingPt& b);

constexpr bool operator>(const FloatingPt& a, const FloatingPt& b);

constexpr bool operator>=(const FloatingPt& a, const FloatingPt& b);

constexpr bool operator<(const FloatingPt& a, const FloatingPt& b);

constexpr bool operator<=(const FloatingPt& a, const FloatingPt& b);

///
/// Negative operator
///
/// @return The negative of `a`
///

constexpr FloatingPt operator-(const FloatingPt& a) { return {-a.value}; }
///
/// Addition operator
///
/// @return the sum of `a` and `b`.
///
constexpr FloatingPt operator+(const FloatingPt& a, const FloatingPt& b)
{
    return {a.value + b.value};
}
///
/// Subtraction operator
///
/// @return the difference of `a` and `b`, e.g. `a - b`.
///
constexpr FloatingPt operator-(const FloatingPt& a, const FloatingPt& b)
{
    return {a.value - b.value};
}
///
/// Multiplication operator
///
/// @return the product of `a` and `b`, e.g. `a * b`.
///
constexpr FloatingPt operator*(const FloatingPt& a, const FloatingPt& b)
{
    return {a.value * b.value};
}

///
/// Division operator
///
/// @return the result of `a` divided by `b`, e.g. `a / b`.
///
constexpr FloatingPt operator/(const FloatingPt& a, const FloatingPt& b)
{
    return {a.value / b.value};
}

///
/// Equality operator
///
/// @return true if a and b are identically equal
/// @return false otherwise
///
constexpr bool operator==(const FloatingPt& a, const FloatingPt& b) { return a.value == b.value; }

///
/// Inequality operator
///
/// @return true if a and b are not equal
/// @return false otherwise
///
constexpr bool operator!=(const FloatingPt& a, const FloatingPt& b) { return !(a == b); }

///
/// Greater-than operator
///
/// @return true if a is greater than b
/// @return false otherwise
///
constexpr bool operator>(const FloatingPt& a, const FloatingPt& b) { return a.value > b.value; }

///
/// Greater-than Equal operator
///
/// @return true if a is greater than or equal to b
/// @return false otherwise
///
constexpr bool operator>=(const FloatingPt& a, const FloatingPt& b) { return a.value >= b.value; }

///
/// Less-than operator
///
/// @return true if a is less than b
/// @return false otherwise
///
constexpr bool operator<(const FloatingPt& a, const FloatingPt& b) { return a.value < b.value; }

///
/// Less-than Equal operator
///
/// @return true if a is less than or equal to b
/// @return false otherwise
///
constexpr bool operator<=(const FloatingPt& a, const FloatingPt& b) { return a.value <= b.value; }
}  // namespace units_internal
}  // namespace bte