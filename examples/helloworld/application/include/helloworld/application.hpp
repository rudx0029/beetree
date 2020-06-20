//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/btos/i-application.hpp"
#include "beetree/engine/tree-extensions.hpp"
#include "beetree/engine/tree.hpp"
#include "beetree/registry/register-provider.hpp"
#include "beetree/registry/register-trace.hpp"
#include "beetree/trace/serial-listener.hpp"
#include "beetree/units/units.hpp"
#include "helloworld-platform/helloworld-platform.hpp"
#include "helloworld/helloworld-model.hpp"
#include "helloworld/registry/helloworld-register-bank.hpp"
#include "helloworld/registry/register-bank-type.hpp"

// > service includes
#include "beetree/services/debug-service.hpp"

namespace helloworld {
class Application : public bte::IApplication
{
public:
    Application() = delete;
    Application(Platform& p) : platform(p) {}

    void sense() override;
    void process() override;
    void actuate() override;
    void on_idle(bool) override;

    // > Application Components
    Platform&                                        platform;
    bte::SerialListener                              trace;
    bte::AllocatedRegisterProvider<RegisterBankType> registry_provider;
    bte::RegisterTrace                               registry_trace;

    // > Trees
    // allocate a tree with stack size of 512 bytes
    bte::Tree<512> tree;

    // > Services
    bte::DebugService debug_svc;

    // > Models
    HelloworldModel helloworld_model;

    // > Facilities
    // <N/A>

    // > Registry
    HelloWorldRegisterBank helloworld_register;
};

}  // namespace helloworld