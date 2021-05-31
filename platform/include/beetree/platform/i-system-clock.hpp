///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file System Clock platform interface
///-----------------------------------------------------------------------------
#pragma once
#include <cstdint>

namespace bte {

struct chrono
{
    /// Platform Timepoint
    using timepoint_ms = int32_t;
    /// Platform Duration
    using duration_ms = int32_t;
    ///
    /// Platform Clock Interface
    ///
    /// Declaration of global time access implemented by a derivative of
    /// ISystemClock. This must be defined and implemented in the application
    /// calling the platform specific System Clock. For Example, in main.cpp, define
    /// the `chrono::now_ms()` method where `MyPlatform` is the targeted platform
    /// defining the hardware.
    /// ```
    /// MyPlatform the_platform;
    ///
    /// namespace bte{
    /// chrono::timepoint_ms chrono::now_ms()
    /// {
    ///     return the_platform.system_clock().now_ms();
    /// }
    /// } // namespace bte
    /// ```
    static timepoint_ms now_ms();
};

///
/// System Clock Interface
///
/// Provides a common interface for providing access to system time.
///
class ISystemClock
{
public:
    ISystemClock()          = default;
    virtual ~ISystemClock() = default;

    ///
    /// @return timepoint_ms  the current time in milli seconds
    /// relative to a power on or reset event
    ///
    virtual chrono::timepoint_ms now_ms() = 0;
};
}  // namespace bte