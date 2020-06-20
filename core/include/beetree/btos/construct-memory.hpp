//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <cstdint>
#include <memory>

namespace bte {
namespace memory {
template <class T>
bool is_valid(const uint8_t* buff, std::size_t len)
{
    return (buff != nullptr) && (sizeof(T) <= len);
}
/// calls T's constructor on the state's data.
/// This must be called before any other operations such as
/// 'ptr<>', 'get<>', and 'set<>'.
/// @return a point to the data type declared by T for convenience
template <class T, class... Args>
T* construct(uint8_t* buff, Args&&... args)
{
    return new (&buff[0]) T(std::forward<Args>(args)...);
}

template <class T>
void destruct(uint8_t* buff)
{
    reinterpret_cast<T*>(&buff[0])->~T();
}

template <class T>
T* fetch(uint8_t* buff)
{
    return reinterpret_cast<T*>(&buff[0]);
}
}  // namespace memory
}  // namespace bte