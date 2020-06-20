//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/engine/runner.hpp"

namespace bte {
Runner::Runner(Engine& engine) : m_engine(&engine) {}

EngineResult Runner::step()
{
    EngineResult result{Status::Fail, false, false};

    if (m_engine) result = m_engine->step();

    return result;
}
}  // namespace bte