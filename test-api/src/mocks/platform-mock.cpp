//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/test/mocks/platform-mock.hpp"

namespace bte {
namespace test {
PlatformMock::SystemClock* s_system_clock = nullptr;
PlatformMock::PlatformMock() { s_system_clock = &system_clock; }
}  // namespace test
}  // namespace bte

namespace bte {
chrono::timepoint_ms chrono::now_ms() { return bte::test::s_system_clock->now_ms(); }
}  // namespace bte
