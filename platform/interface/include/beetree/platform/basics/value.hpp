//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include <cstdint>
#include <atomic>

namespace bte {
namespace registry {
class Value
{
public:
    Value() = default;
    inline Value(uint32_t value);

    // uint32_t conversions
    inline Value& operator=(uint32_t value);
    inline operator uint32_t() const;

    // int32_t conversions
    inline Value& operator=(int32_t value);
    inline operator int32_t() const;

    // bool conversions
    inline Value& operator=(bool value);

    // conversion helpers
    inline static int32_t to_signed(uint32_t value);
    inline static uint32_t from_signed(int32_t value);

private:
    std::atomic_uint32_t m_value{0};
};

Value::Value(uint32_t value) : m_value(value) {}

// uint32_t conversions
Value& Value::operator=(uint32_t value)
{
    m_value = value;
    return *this;
}

// int32_t conversions
Value& Value::operator=(int32_t value)
{
    m_value = from_signed(value);
    return *this;
}

// bool conversions
Value& Value::operator=(bool value)
{
    m_value = value ? 1 : 0;
    return *this;
}

// uint32_t conversions
Value::operator uint32_t() const { return m_value; }

// int32_t conversions
Value::operator int32_t() const { return to_signed(m_value); }

int32_t Value::to_signed(uint32_t value) { return *(reinterpret_cast<int32_t*>(&value)); }
uint32_t Value::from_signed(int32_t value) { return *(reinterpret_cast<uint32_t*>(&value)); }

}  // namespace registry
}  // namespace bte