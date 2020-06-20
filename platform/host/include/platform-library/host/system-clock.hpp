//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/platform/i-system-clock.hpp"

namespace host {
///
/// Represents an instance of the System Clock for host devices.
///
class SystemClock : public bte::ISystemClock
{
public:
    SystemClock() = default;

    ///
    /// Gets the current time in milli seconds from the system clock
    ///
    /// @return chrono::timepoint_ms  the time in milliseconds
    ///
    bte::chrono::timepoint_ms now_ms() override;
};
}  // namespace host