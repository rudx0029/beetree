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
class RegisterValue
{
public:
    RegisterValue() = default;
    inline RegisterValue(uint32_t value);

    // uint32_t conversions
    inline RegisterValue& operator=(uint32_t value);
    inline operator uint32_t() const;

    // int32_t conversions
    inline RegisterValue& operator=(int32_t value);
    inline operator int32_t() const;

    // bool conversions
    inline RegisterValue& operator=(bool value);
    inline operator bool() const;

    // conversion helpers
    inline static int32_t to_signed(uint32_t value);
    inline static uint32_t from_signed(int32_t value);

private:
    std::atomic_uint32_t m_value{0};
};

RegisterValue::RegisterValue(uint32_t value) : m_value(value) {}

// uint32_t conversions
RegisterValue& RegisterValue::operator=(uint32_t value)
{
    m_value = value;
    return *this;
}

// int32_t conversions
RegisterValue& RegisterValue::operator=(int32_t value)
{
    m_value = from_signed(value);
    return *this;
}

// bool conversions
RegisterValue& RegisterValue::operator=(bool value)
{
    m_value = value ? 1 : 0;
    return *this;
}

// uint32_t conversions
RegisterValue::operator uint32_t() const { return m_value; }

// int32_t conversions
RegisterValue::operator int32_t() const { return to_signed(m_value); }

// bool conversions
RegisterValue::operator bool() const { return m_value != 0; }

int32_t RegisterValue::to_signed(uint32_t value) { return *(reinterpret_cast<int32_t*>(&value)); }
uint32_t RegisterValue::from_signed(int32_t value) { return *(reinterpret_cast<uint32_t*>(&value)); }
}  // namespace bte