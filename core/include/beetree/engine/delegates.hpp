///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------
#pragma once

#include "beetree/engine/exception.hpp"
#include "beetree/engine/result.hpp"
#include "beetree/engine/status.hpp"
#include "beetree/trace/trace-stream.hpp"

namespace bte {
// > Forward Declarations
struct Context;
struct Recipe;

struct delegate
{
    // > Node Build
    using Build = Recipe (*)();

    // > Node Interface
    using Loop      = Result (*)(Context&);
    using Setup     = void (*)(Context&);
    using Teardown  = void (*)(Context&);
    using Construct = void (*)(Context&);
    using Destruct  = void (*)(Context&);

    // > Node Interface with State
    template <class TState>
    using Loop_s = Result (*)(Context&, TState&);
    template <class TState>
    using Setup_s = void (*)(Context&, TState&);

    // > Node Events
    using ExceptionEvt      = void (*)(const Exception&, Context&);
    using BranchCompleteEvt = void (*)(Status, Context&);
    using TraceEvt          = void (*)(TraceStream&, Context&);

    // > Node Events With State
    template <class TState>
    using ExceptionEvt_s = void (*)(const Exception&, Context&, TState&);
    template <class TState>
    using BranchCompleteEvt_s = void (*)(Status, Context&, TState&);
    template <class TState>
    using TraceEvt_s = void (*)(TraceStream&, Context&, TState&);

    // > Misc
    using Predicate = bool (*)();
    using Action    = void (*)();
};
}  // namespace bte