//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include "beetree/units/internal/transforms.hpp"

namespace bte {
namespace units_internal {
///
/// Creates a label for unit. For example, given the quantity length, the
/// unit is Unit<quantity::Length>. Then the label is meters or millimeters.
///
/// @tparam Q The quantity the label refers too.
/// @tparam R The ratio between the SI units of the same quantity
/// @tparam nominally transforms::Identity, a conversion routine like
/// Deg2Rad to transform a value specified by the label into the appropriate
/// quantity.
///
template <class Q, class R, class T = Transforms::Identity>
struct Label
{
    using quantity  = Q;
    using ratio     = R;
    using transform = T;
};
}  // namespace units_internal
}  // namespace bte