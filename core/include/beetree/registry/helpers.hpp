#pragma once

#include <cstdint>

namespace bte {
inline int32_t to_signed(uint32_t value) { return *(reinterpret_cast<int32_t*>(&value)); }

inline uint32_t from_signed(int32_t value) { return *(reinterpret_cast<uint32_t*>(&value)); }
}  // namespace bte