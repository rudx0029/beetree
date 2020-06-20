//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include "beetree/btos/collection.hpp"
#include "beetree/registry/register-bank.hpp"

namespace bte {

///
/// A register provider is a collection of register banks [references], where a register
/// bank is a collection of data items.
///
///
using RegisterProvider = Collection<RegisterBank>;

template <class TRegisterEnum>
using AllocatedRegisterProvider =
    AllocatedCollection<RegisterBank,
                        static_cast<std::size_t>(TRegisterEnum::NUM_BANKS),
                        TRegisterEnum>;
}  // namespace bte