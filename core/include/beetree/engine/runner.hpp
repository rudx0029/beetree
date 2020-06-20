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
/// The Runner allows its caller to invoke a step on the tree
/// without directly accessing the engine. It is preferred to use
/// the Runner over directly invoking the engine, but it is not required.
///
class Runner
{
public:
    Runner() = default;
    Runner(Engine& engine);

    ///
    /// invokes a step through the tree, cycling the nodes.
    ///
    /// @return EngineResult the result of the engine stepping through the
    /// tree.
    ///
    EngineResult step();

private:
    Engine* m_engine = nullptr;
};
}  // namespace bte