//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/trace/trace-defs.hpp"

namespace bte {
namespace trace_prot {
std::size_t package(TraceProcessor proccess, const TracePackage& package, uint8_t buffer[BUF_LEN]);
}  // namespace trace_prot
}  // namespace bte