//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/platform/i-serial-device.hpp"
#include "beetree/trace/trace-manager.hpp"

namespace bte {
class SerialListener : public TraceListener
{
public:
    SerialListener() = default;

    void on_log_received(TraceProcessor processor, const TracePackage& package) override;
    void configure(ISerialDevice& out, TraceVerbosity verb);

private:
    TraceManager   m_manager;
    ISerialDevice* m_out = nullptr;
};
}  // namespace bte