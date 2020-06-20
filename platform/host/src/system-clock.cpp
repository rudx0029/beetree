//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include <chrono>
#include <limits>
#include "platform-library/host/system-clock.hpp"

namespace host {
namespace {
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
steady_clock::time_point m_start{steady_clock::duration{0}};
}  // namespace

bte::chrono::timepoint_ms SystemClock::now_ms()
{
    if (m_start.time_since_epoch() == steady_clock::duration{0})
    {
        m_start = steady_clock::now();
    }

    auto now_ms = duration_cast<milliseconds>(steady_clock::now() - m_start).count();

    return static_cast<int32_t>(now_ms);
}
}  // namespace host