//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include <cstdint>

namespace bte {
struct BumpModel
{
    uint32_t bump_zone   = 0;  // bump mask
    bool     bump_active = false;
};
}  // namespace bte