//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/trace/trace.hpp"

namespace bte {

///
/// Immediately halts the application and calls the assert handler. This is
/// equivalent of calling assert(false);
///
/// @param token the assert message
///
void fail(const TraceToken& token);

///
/// Asserts that the value is true. If the value is false, the
/// application immediately halts and calls the assert handler.
///
/// @param value the value to assert true.
/// @param token  the assert message when the assert fails.
///
inline void assert_true(bool value, const TraceToken& token)
{
    if (!value) fail(token);
}

///
/// Asserts that the pointer is not null. If the pointer is null, the
/// application immediately halts and calls the assert handler.
///
/// @param value the value to assert true.
/// @param token  the assert message when the assert fails.
///
inline void assert_valid(const void* ptr, const TraceToken& token)
{
    if (nullptr == ptr) fail(token);
}

struct Assert
{
    ///
    /// Handler interface to override default assert handler.
    ///
    class IHandler
    {
    public:
        virtual void on_fail(const TraceToken& token);
    };

    ///
    /// installs the assert handler that overrides the default implementation
    /// for handling asserts.
    ///
    static void install(IHandler& handler);
};
}  // namespace bte