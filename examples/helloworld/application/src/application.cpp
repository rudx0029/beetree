//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "helloworld/application.hpp"

namespace helloworld {

void Application::sense()
{
    // update the model from the platform
    helloworld_model.user_btn_depressed = platform.user_btn().is_set();

    // update the registry
    this->helloworld_register[HelloWorldKeys::USER_BTN_DEPRESSED] =
        helloworld_model.user_btn_depressed;
}

void Application::process() { bte::TreeX::loop(this->tree, 10_ms); }

void Application::actuate() {}  // nothing to actuate

void Application::on_idle(bool first_time)
{
    // advance the registry trace only once per scan
    if (first_time)
    {
        registry_trace.tick();
    }
}
}  // namespace helloworld