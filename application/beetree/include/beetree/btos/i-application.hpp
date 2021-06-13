//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/btos/clock.hpp"

namespace bte {
class IApplication
{
public:
    IApplication()          = default;
    virtual ~IApplication() = default;

    virtual void sense()   = 0;
    virtual void process() = 0;
    virtual void actuate() = 0;

    // events - non-blocking and quick!
    virtual void on_overrun(Clock::ms duration) {}
    virtual void on_idle(bool first_time){};
};

}  // namespace bte