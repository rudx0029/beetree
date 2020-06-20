//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE.txt', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/nodes/blackboard.hpp"
#include "beetree/core/tokens.hpp"
#include "beetree/btos/assert.hpp"

namespace bte {
void bte::blackboard::assert_valid_source(const void* src)
{
    assert_valid(src, tokens::FatalNotFound);
}
}  // namespace bte