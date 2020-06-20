//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#include "beetree/registry/register-trace.hpp"
#include "beetree/core/tokens.hpp"

namespace bte {
void RegisterTrace::install(const RegisterProvider& provider)
{
    m_provider = provider;

    if (m_provider.is_valid())  // valid if it has at least one bank
    {
        m_all_banks_valid = true;  // assume true

        for (auto bank : m_provider)
        {
            m_all_banks_valid = bank.is_valid();
            if (!m_all_banks_valid) break;
        }

        if (m_all_banks_valid)
        {
            m_cur_bank = m_provider.begin();
            m_cur_item = m_cur_bank->begin();
        }
    }
}

void RegisterTrace::tick()
{
    if (m_all_banks_valid)
    {
        trace::channels::registry(tokens::RegistryItem)
            << RegisterProvider::to_index(m_provider, m_cur_bank)
            << RegisterBank::to_index(*m_cur_bank, m_cur_item)
            << static_cast<uint32_t>(*m_cur_item);

        m_cur_item++;

        if (m_cur_item >= m_cur_bank->end())
        {
            m_cur_bank++;
            if (m_cur_bank >= m_provider.end())
            {
                m_cur_bank = m_provider.begin();
            }

            m_cur_item = m_cur_bank->begin();
        }
    }
}

}  // namespace bte