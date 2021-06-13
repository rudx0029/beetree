//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include <type_traits>
#include "beetree/btos/collection.hpp"
#include "beetree/registry/item.hpp"

namespace bte {

///
/// A RegisterBank is a collection of data items (uint32_t value).
/// This collection is typically arranged as an array.  The register bank is to
/// be a collection of related values where each value can be represented as a
/// data_type, e.g. uint32_t.
///
///
using RegisterBank = Collection<Item>;

template <class TDataEnum>
using AllocatedRegisterBank =
    AllocatedCollection<Item, static_cast<std::size_t>(TDataEnum::NUM_ITEMS), TDataEnum>;
}  // namespace bte