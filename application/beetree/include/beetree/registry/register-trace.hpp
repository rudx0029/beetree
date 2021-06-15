//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include "beetree/registry/register-bank.hpp"
#include "beetree/registry/register-provider.hpp"
#include "beetree/trace/trace.hpp"

namespace bte {
class RegisterTrace
{
public:
    RegisterTrace() = default;

    void install(const RegisterProvider& provider);

    void tick();

private:
    RegisterProvider                 m_provider;
    RegisterProvider::const_iterator m_cur_bank        = RegisterProvider::null_iterator;
    RegisterBank::const_iterator     m_cur_item        = RegisterBank::null_iterator;
    bool                             m_all_banks_valid = false;
};
}  // namespace bte