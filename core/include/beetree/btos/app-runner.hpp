//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/btos/i-application.hpp"

namespace bte {
void run(IApplication& application, Clock::milliseconds scan_interval, void (*yield)() = nullptr);
}  // namespace bte