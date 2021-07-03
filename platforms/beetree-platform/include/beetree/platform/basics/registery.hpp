//------------------------------------------------------------------------------
// Copyright (C) 2021 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
/// @file Definitions for Beetree's registry

#pragma once

#include <atomic>

namespace bte {
namespace registry {
struct Value
{
    using data_type = uint32_t;
    data_type data;
};

using value_type  = Value;
using atomic_type = std::atomic<value_type>;

template <class T>
inline value_type make(const T& value);

template <class T>
inline T as(const registry::value_type& rval);

template <>
inline value_type make<bool>(const bool& value)
{
    return value_type{(value ? 1U : 0U)};
}

template <>
inline bool as<bool>(const registry::value_type& rval)
{
    return rval.data == 0 ? false : true;
}

template <>
inline value_type make<int32_t>(const int32_t& value)
{
    static_assert(sizeof(int32_t) == sizeof(value_type::data_type),
                  "int32_t must be same size as registry::value_type::data_type");
    const int32_t*               value_ptr = &value;
    const value_type::data_type* uvalue_ptr =
        reinterpret_cast<const value_type::data_type*>(value_ptr);
    return {*uvalue_ptr};
}

template <>
inline int32_t as<int32_t>(const registry::value_type& rval)
{
    static_assert(sizeof(int32_t) == sizeof(value_type::data_type),
                  "int32_t must be same size as registry::value_type::data_type");
    const value_type::data_type* rval_ptr  = &rval.data;
    const int32_t*               int32_ptr = reinterpret_cast<const int32_t*>(rval_ptr);
    return *int32_ptr;
}

template <>
inline value_type make<float>(const float& value)
{
    static_assert(sizeof(float) == sizeof(value_type::data_type),
                  "float must be same size as registry::value_type::data_type");

    const float*                 value_ptr = &value;
    const value_type::data_type* uvalue_ptr =
        reinterpret_cast<const value_type::data_type*>(value_ptr);
    return {*uvalue_ptr};
}

template <>
inline float as<float>(const registry::value_type& rval)
{
    static_assert(sizeof(float) == sizeof(value_type::data_type),
                  "float must be same size as registry::value_type::data_type");
    const value_type::data_type* rval_ptr  = &rval.data;
    const float*                 float_ptr = reinterpret_cast<const float*>(rval_ptr);
    return *float_ptr;
}

template <>
inline value_type make<uint32_t>(const uint32_t& value)
{
    return {value};
}

template <>
inline uint32_t as<uint32_t>(const registry::value_type& rval)
{
    return rval.data;
}

// template<class T>
// inline value_type make(const T& value){
//     static_assert(false, "not implemented");
//     return value_type{};
// }

// template<class T>
// inline T as(const registry::value_type& rval) {
//     static_assert(false, "not implemented");
//     return T{};
// }
}  // namespace registry
}  // namespace bte