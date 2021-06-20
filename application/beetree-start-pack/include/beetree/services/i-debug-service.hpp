//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

namespace bte {
class IDebugService
{
public:
    struct Model
    {
        bool is_led_set{false};
        bool is_debug_pin_set{false};
    };

    virtual const Model& model() const      = 0;
    virtual void         toggle_led()       = 0;
    virtual void         toggle_debug_pin() = 0;
    virtual void         feed_the_dog()     = 0;

    //-----------------------------------
    IDebugService()                     = default;
    virtual ~IDebugService()            = default;
    IDebugService(const IDebugService&) = delete;
    IDebugService(IDebugService&&)      = delete;
    IDebugService& operator=(const IDebugService&) = delete;
    IDebugService& operator=(IDebugService&&) = delete;
};
}  // namespace bte