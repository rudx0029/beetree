///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///
/// @file
///-----------------------------------------------------------------------------
#pragma once

#include <cstdint>

namespace bte {
enum class ExceptionType
{
    ///
    /// This is a general purpose exception and there is no specification
    /// when it should be thrown.
    /// argument:
    ///    unspecified
    /// node:
    ///    try_catch_all
    ///
    ALL,
    ///
    /// Thrown when a reflex has been activated
    /// argument:
    ///    reflex's id represented as a bitmask value, ranging from 0,
    ///    inclusive to 32 exclusive.
    /// node:
    ///    try_catch_reflex
    ///
    REFLEX,
    ///
    /// Thrown when a user event occurs like a button press.
    /// argument:
    ///    unspecified
    /// node:
    ///    try_catch_user
    ///
    USER
};

//-----------------------------------------
// Exception Objects
//-----------------------------------------

struct Exception
{
    constexpr Exception() = default;
    constexpr Exception(ExceptionType type, uint32_t arg = 0) : m_type(type), m_arg(arg) {}

    constexpr ExceptionType type() const { return m_type; }
    constexpr uint32_t      arg() const { return m_arg; }

private:
    ExceptionType m_type = ExceptionType::ALL;
    uint32_t      m_arg  = 0;
};

///
/// Template to create Typed Exceptions based on the Enumeration
/// The template uses an implicit conversion operator to change the
/// type to an Exception carrying the type as an enumeration
///
template <ExceptionType TYPE>
struct TypeException
{
public:
    constexpr TypeException(uint32_t arg = 0) : m_arg(arg) {}

    // implicit conversion operator
    operator Exception() { return Exception(TYPE, m_arg); }

private:
    uint32_t m_arg = 0;
};

/// The Typed Exceptions based on the Exception Type Enumeration
using UserException   = TypeException<ExceptionType::USER>;
using ReflexException = TypeException<ExceptionType::REFLEX>;
}  // namespace bte