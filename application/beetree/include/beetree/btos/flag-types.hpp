//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <cstdint>
#include <type_traits>

namespace bte {

///
/// A strongly typed bitmap to be used with the Flags collection.
///
/// Usage:
/// ```
/// struct MyType{}; //unique type
/// using MyFlag = Flag<MyType>;
///
/// // 0 bit flag, value = 0x00000001
/// constexpr MyFlag FLAG_1 = MyFlag::make<0>();
///
/// // 31st bit flag, value = 0x10000000
/// constexpr MyFlag FLAG_2 = MyFlag::make<31>();
/// ```
///
/// @tparam TYPE a named type to individual qualify the type for the collection
/// of flags
///
template <class TYPE>  // to strongly type it
struct Flag
{
    ///
    /// The flag's bitmap value.
    ///
    const uint32_t value = 0;

    ///
    /// [compile-time] factory for creating and specifying flags.
    ///
    /// @tparam FLAG the bitmap flag position from 0 to 31
    /// @return the flag
    ///
    template <uint32_t FLAG>
    static constexpr Flag make()
    {
        static_assert(FLAG < 32, "the reflex flag must be less than 32");
        return Flag(1 << FLAG);
    }

private:
    constexpr Flag(uint32_t bitmap_value) : value(bitmap_value) {}
};

///
/// Strongly typed bitmask to be used with Flag<> or an Enumeration
///
/// @tparam TYPE either an enumeration or the named type in Flag<>.
///
template <class TYPE>
struct Flags
{
    uint32_t bitmask = 0;

    Flags() = default;
    Flags(uint32_t init_bitmask) : bitmask(init_bitmask) {}
};

}  // namespace bte