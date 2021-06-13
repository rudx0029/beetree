///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file default system clock @ 48 mhz for stm32 processors
///-----------------------------------------------------------------------------

#pragma once

#include "beetree/platform/i-system-clock.hpp"

namespace stm32f1xx {
///
/// Represents an instance of the System Clock for stm32f1xx devices.
///
class SystemClock : public bte::ISystemClock
{
public:
    SystemClock() = default;

    ///
    /// Handler for 'systick' interrupt
    ///
    void on_interrupt();

    ///
    /// Gets the current time in milli seconds since 'power on' or the last
    /// reset.
    ///
    /// @return platform::timepoint_ms  the time in milliseconds
    ///
    bte::chrono::timepoint_ms now_ms() override;

private:
    volatile bte::chrono::timepoint_ms m_systick = 0;
};
}  // namespace stm32f1xx