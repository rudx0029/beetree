///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------

#pragma once

#include "beetree/engine/context.hpp"
#include "beetree/engine/select-algorithm.hpp"

namespace bte {
namespace internal {

using TryCatchData = SelectAlgorithm::Data;

bool is_try_catch_node(const Node& n);
bool is_try_catch_node_strict(const Node& n, ExceptionType ex);

bool is_try_active(TryCatchData* data, const Context& context);

bool is_catch_active(TryCatchData* data, const Context& context);

bool can_clear_exception();
}  // namespace internal
}  // namespace bte