///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
///-----------------------------------------------------------------------------

#pragma once

#include "beetree/engine/node.hpp"
#include "beetree/engine/recipe.hpp"

namespace bte {
Recipe try_catch_all();
Recipe try_catch_reflex();
Recipe try_catch_user();

using TryCatchAll    = Composite<try_catch_all>;
using TryCatchReflex = Composite<try_catch_reflex>;
using TryCatchUser   = Composite<try_catch_user>;
}  // namespace bte