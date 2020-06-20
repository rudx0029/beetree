//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/node.hpp"
#include "beetree/nodes/idle-internal.hpp"

namespace bte {

///
/// @ingroup nodes
///
/// Idle
/// ====
///
/// The Idle node pauses execution of the tree for Duration amount of time and
/// returns Success when done.
///
/// Usage
/// -----
///
/// ```cpp
/// constexpr Clock::ms Duration = 500_ms;
/// constexpr Idle<Duration> sleep_500ms;
/// ```
///
/// Parameters
/// ----------
///
/// |          |                               |
/// |----------|-------------------------------|
/// | Duration | amount of time to be idle for |
///
/// Returns
/// -------
///
/// |                           |                            |
/// |---------------------------|----------------------------|
/// | `Result{Status::Running}` | during idle duration       |
/// | `Result{Status::Success}` | always after idle duration |
///
template <const Clock::ms& Duration>
using Idle = Leaf<make_idle<Duration>>;

}  // namespace bte