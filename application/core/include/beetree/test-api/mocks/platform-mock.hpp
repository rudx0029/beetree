//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/test-api/mocks/mock-platform-interfaces.hpp"

namespace bte {
namespace test {
///
/// Convenience Platform Mock that installs itself into the underlying unit test
/// platform.
///
class PlatformMock
{
public:
    using SystemClock = gtest::NiceMock<MockSystemClock>;
    SystemClock system_clock;

    PlatformMock();

    SystemClock& operator*() { return system_clock; }
};
}  // namespace test
}  // namespace bte