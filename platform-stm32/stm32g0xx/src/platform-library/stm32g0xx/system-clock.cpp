///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#include "beetree/platform/stm32g0xx/system-clock.hpp"
#include <limits>

namespace stm32g0xx {
void SystemClock::on_interrupt() { m_systick++; }

bte::chrono::timepoint_ms SystemClock::now_ms()
{
    constexpr std::uint32_t max_int32_t =
        static_cast<std::uint32_t>(std::numeric_limits<std::int32_t>::max());

    // known roll over issue if tick gets above std::numeric_limit<int32_t>::max()
    std::uint32_t tick = m_systick;
    return static_cast<bte::chrono::timepoint_ms>(tick <= max_int32_t ? tick : tick - max_int32_t);
}
}  // namespace stm32f0xx
