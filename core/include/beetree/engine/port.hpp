///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#pragma once

#include "beetree/engine/node.hpp"
#include "beetree/engine/recipe.hpp"

namespace bte {
Recipe port_optional();
Recipe port_mandatory();

using PortOptional  = Leaf<port_optional>;
using PortMandatory = Leaf<port_mandatory>;
}  // namespace bte