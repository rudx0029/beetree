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
    const IDebugService::Model& model() const override { return m_model; }

    void toggle_led() override
    {
        m_model.is_led_set = !m_model.is_led_set;
    }
    void toggle_debug_pin() override
    {
        m_model.is_debug_pin_set = !m_model.is_debug_pin_set;
    }
    void feed_the_dog() override
    { /*TODO*/
    }

private:
    IDebugService::Model m_model;
};
}  // namespace bte