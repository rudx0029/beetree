//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include <cstdint>

namespace bte {
class Item
{
public:
    Item() = default;
    Item(uint32_t value);

    // uint32_t conversions
    Item& operator=(uint32_t value);
          operator uint32_t() const;

    // int32_t conversions
    Item& operator=(int32_t value);
          operator int32_t() const;

    // bool conversions
    Item& operator=(bool value);

private:
    uint32_t m_value = 0;
};
}  // namespace bte