//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include <cstdint>

namespace bte {
namespace units_internal {
///
/// Ratios are used to help convert between SI units of the same
/// quantity, e.g. milli-meters and meters, milli-radians and radians.
///
template <int32_t NUM, int32_t DEN = 1>
struct Ratio
{
    static constexpr int num = NUM;
    static constexpr int den = DEN;
};

struct Ratios
{
    // define ratios in terms of SI units, outside of a ratio of 1. Uno is reserved for that
    using nano     = Ratio<1, 1000000000>;
    using micro    = Ratio<1, 1000000>;
    using milli    = Ratio<1, 1000>;
    using centi    = Ratio<1, 100>;
    using deci     = Ratio<1, 10>;
    using identity = Ratio<1, 1>;
    using kilo     = Ratio<1000, 1>;
};

}  // namespace units_internal
}  // namespace bte