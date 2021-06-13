//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/btos/clock.hpp"
#include "beetree/trace/trace-defs.hpp"
#include "beetree/trace/trace-manager.hpp"

namespace bte {
class TraceStream
{
public:
    TraceStream(TraceManager*     manager,
                const TraceToken& token,
                TraceChannel      channel,
                TraceVerbosity    verbosity);
    TraceStream(TraceStream&&);
    TraceStream(const TraceStream&) = delete;

    ~TraceStream();

    TraceStream& operator=(const TraceStream&) = delete;
    TraceStream& operator=(TraceStream&&) = delete;

    TraceStream& operator<<(uint64_t arg);  // ! down cast to uint32_t
    TraceStream& operator<<(int64_t arg);   // ! down cast to int32_t

    TraceStream& operator<<(uint32_t arg);
    TraceStream& operator<<(int32_t arg);

    TraceStream& operator<<(uint16_t arg);
    TraceStream& operator<<(int16_t arg);

    TraceStream& operator<<(uint8_t arg);
    TraceStream& operator<<(int8_t arg);

    TraceStream& operator<<(float arg);
    TraceStream& operator<<(double arg);
    TraceStream& operator<<(bte::Clock::milliseconds arg);
    TraceStream& operator<<(bool arg);
    TraceStream& operator<<(const TraceToken& token);
    TraceStream& operator<<(const char* msg);

private:
    void add_argument(uint32_t);

    TracePackage  m_package;
    TraceManager* m_manager = nullptr;
};
}  // namespace bte