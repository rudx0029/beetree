//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/platform/i-discrete-output.hpp"
#include "beetree/services/i-debug-service.hpp"

namespace bte {

class DebugService : public IDebugService
{
public:
    void configure(IDiscreteOutput& toggle_led, IDiscreteOutput& debug_pin)
    {
        m_toggle_led = &toggle_led;
        m_debug_pin  = &debug_pin;
    }
    void toggle_led() override
    {
        if (m_toggle_led) m_toggle_led->toggle();
    }
    void toggle_debug_pin() override
    {
        if (m_debug_pin) m_debug_pin->toggle();
    }
    void feed_the_dog() override
    { /*TODO*/
    }

private:
    IDiscreteOutput* m_toggle_led = nullptr;
    IDiscreteOutput* m_debug_pin  = nullptr;
};
}  // namespace bte