//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/platform/i-analog-input.hpp"
#include "beetree/platform/i-analog-output.hpp"
#include "beetree/platform/i-system-clock.hpp"
#include "beetree/test/gtest-ns.hpp"

namespace bte {
namespace test {
///
/// Mock for bte::IAnalogInput
///
class MockAnalogOutput : public IAnalogOutput
{
public:
    MOCK_METHOD1(write, void(uint32_t value));
};
///
/// Mock for bte::IAnalogInput
///
class MockAnalogInput : public IAnalogInput
{
public:
    MOCK_METHOD0(read, uint32_t());
};
///
/// Mock for bte::ISystemClock
///
class MockSystemClock : public ISystemClock
{
public:
    MOCK_METHOD0(now_ms, chrono::timepoint_ms());
};
}  // namespace test
}  // namespace bte