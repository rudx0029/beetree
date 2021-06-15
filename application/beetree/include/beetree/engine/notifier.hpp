//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/engine.hpp"

namespace bte {
///
/// Allows interested parties to notify a given tree with an exception. It
/// is recommended to use the Notifier object versus calling a tree's engine
/// directly.
///
class Notifier
{
public:
    Notifier() = default;
    Notifier(Engine& engine);

    ///
    /// Raises an exception on tree owned by the engine.
    ///
    /// @param ex the exception to raise
    ///
    void raise(const Exception& ex);

private:
    Engine* m_engine = nullptr;
};
}  // namespace bte