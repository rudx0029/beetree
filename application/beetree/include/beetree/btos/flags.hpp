//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <limits>
#include "beetree/btos/flag-types.hpp"

namespace bte {
///
/// The flags namespace includes bit mask operations for the Flags<> bitmask
/// type. The operations can be used with enumerations and the strongly typed
/// Flag<>. You would choose the Flag<> type over an enumeration when you wish
/// not to constrict your self with an enumeration. This is the case with the
/// Reflex type since different developers/designers/venders may not want to be
/// constricted with a limited set of reflexes represented by a single
/// enumeration.
///
/// # API
/// The api follow suit with the std::bitset api but in functional form. This is
/// to allow POD to include Flags<> with out bringing along the implementation.
///
/// `flags::set(F, f)`
/// :   sets the flag `f` in flags `F` and returns true if `F` is modified
/// `flags::set(F)`
/// :   sets all the flags in `F` and returns true if `F` is modified
/// `flags::reset(F, f)`
/// :   clears the flag `f` in flags `F` and returns true if `F` is modified
/// `flags::reset(F)`
/// :   clears all the flags in `F` and returns true if `F` is modified
/// `flags::test(F,f)`
/// :   returns true if the flag 'f' is set in flags 'F'
/// `flags::all(F)`
/// :   returns true if all the flags are set in flags `F`
/// `flags::any(F)`
/// :   returns true if any flags are set in flags `F`
/// `flags::none(F)`
/// :   returns true when no flags are set in flags `F`
///
/// # Usage With Enumerations
/// ```
/// enum class MyBitMap {
///     BIT_0,
///     BIT_1
/// };
/// ...
/// Flags<MyBitMap> F;
/// flags::set(F, MyBitMap::BIT_1);
/// assert(!flags::none(F) && !flags::all(F)
///                        && !flags::test(F,MybitMap::BIT_0));
/// assert(flags::test(F, MyBitMap::BIT_1)
///        && flags::any(F));
/// ```
///
/// # Usage with Flag type
/// ```
/// struct StrongType{};
/// using MyFlag = Flag<StrongType>;
/// using MyFlags = Flags<StrongType>;
///
/// constexpr MyFlag BIT_0 = MyFlag::make<0>();
/// constexpr MyFlag BIT_1 = MyFlag::make<1>();
/// ...
/// MyFlags F;
/// flags::set(F, BIT_1);
/// assert(!flags::none(F) && !flags::all(F)
///                        && !flags::test(F,BIT_0));
/// assert(flags::test(F, BIT_1)
///        && flags::any(F));
/// ```
///
namespace flags {

// ----
template <class TEnum>
using enum_method = typename std::enable_if<std::is_enum<TEnum>::value>::type;
template <class TFlag>
using flag_method = typename std::enable_if<!std::is_enum<TFlag>::value>::type;

template <class TEnum>
uint32_t to_bitmask(TEnum flag)
{
    return 1 << static_cast<uint32_t>(flag);
}
///
/// test
/// (using enumerations)
///
template <class TEnum, typename = enum_method<TEnum>>
bool test(const Flags<TEnum>& flags, TEnum flag)
{
    return (flags.bitmask & to_bitmask(flag)) != 0;
}
///
/// test
/// (using Flags<>)
///
template <class TFlag, typename = flag_method<TFlag>>
bool test(const Flags<TFlag>& flags, const Flag<TFlag>& flag)
{
    return (flags.bitmask & flag.value) != 0;
}
///
/// any
///
template <class T>
bool any(const Flags<T>& flags)
{
    return flags.bitmask != 0;
}
///
/// none
///
template <class T>
bool none(const Flags<T>& flags)
{
    return flags.bitmask == 0;
}
///
/// all
///
template <class T>
bool all(const Flags<T>& flags)
{
    return flags.bitmask == std::numeric_limits<uint32_t>::max();
}
///
/// set
/// (using enumerations)
///
template <class TEnum, typename = enum_method<TEnum>>
bool set(Flags<TEnum>& flags, TEnum flag)
{
    bool changed = !test(flags, flag);
    flags.bitmask |= to_bitmask(flag);
    return changed;
}
///
/// set
/// (using Flag<>)
///
template <class TFlag, typename = flag_method<TFlag>>
bool set(Flags<TFlag>& flags, const Flag<TFlag>& flag)
{
    bool changed = !test(flags, flag);
    flags.bitmask |= flag.value;
    return changed;
}
///
/// set all
///
template <class T>
bool set(Flags<T>& flags)
{
    bool changed  = !all(flags);
    flags.bitmask = std::numeric_limits<uint32_t>::max();
    return changed;
}

///
/// reset
/// (using enumerations)
///
template <class TEnum, typename = enum_method<TEnum>>
bool reset(Flags<TEnum>& flags, TEnum flag)
{
    bool changed = test(flags, flag);
    flags.bitmask &= ~to_bitmask(flag);
    return changed;
}
///
/// reset
/// (using Flag<>)
///
template <class TFlag, typename = flag_method<TFlag>>
bool reset(Flags<TFlag>& flags, const Flag<TFlag>& flag)
{
    bool changed = test(flags, flag);
    flags.bitmask &= ~flag.value;
    return changed;
}
///
/// reset all
///
template <class T>
bool reset(Flags<T>& flags)
{
    bool changed  = any(flags);
    flags.bitmask = 0;
    return changed;
}
}  // namespace flags
}  // namespace bte