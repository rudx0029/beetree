#pragma once

#include "beetree/models/data/reflex.hpp"

namespace bte {
struct ReflexesModel
{
    ///
    /// true when reflex subsystem is enabled
    ///
    bool is_enabled = true;
    ///
    /// bitmask of currently active reflexes
    ///
    Reflexes current_reflexes;
};
}  // namespace bte