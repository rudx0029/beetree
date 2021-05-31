//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/core/tokens.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/engine/result.hpp"
#include "beetree/nodes/fail.hpp"
#include "beetree/nodes/null.hpp"
#include "beetree/nodes/success.hpp"

namespace bte {

static Result loop_success(Context&) { return Status::Success; }
static Result loop_fail(Context&) { return Status::Fail; }

Recipe make_success() { return Builder(tokens::SuccessNode, loop_success).finalize(); }
Recipe make_null() { return Builder(tokens::NullNode, loop_success).finalize(); }
Recipe make_fail() { return Builder(tokens::FailNode, loop_fail).finalize(); }
}  // namespace bte