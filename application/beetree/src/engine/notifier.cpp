//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/engine/notifier.hpp"

namespace bte {
Notifier::Notifier(Engine& engine) : m_engine(&engine) {}

void Notifier::raise(const Exception& ex)
{
    if (m_engine) m_engine->on_exception(ex);
}
}  // namespace bte