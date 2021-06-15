//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/registry/helpers.hpp"
#include "beetree/registry/item.hpp"


namespace bte {

Item::Item(uint32_t value) : m_value(value) {}

// uint32_t conversions
Item& Item::operator=(uint32_t value)
{
    m_value = value;
    return *this;
}

// int32_t conversions
Item& Item::operator=(int32_t value)
{
    m_value = from_signed(value);
    return *this;
}

// bool conversions
Item& Item::operator=(bool value)
{
    m_value = value ? 1 : 0;
    return *this;
}

// uint32_t conversions
Item::operator uint32_t() const { return m_value; }

// int32_t conversions
Item::operator int32_t() const { return to_signed(m_value); }

}  // namespace bte