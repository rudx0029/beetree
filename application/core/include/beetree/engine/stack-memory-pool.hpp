///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------
#pragma once

#include "beetree/btos/memory.hpp"

namespace bte {
class StackMemoryPool : public MemoryPool
{
public:
    struct Header
    {
        std::size_t len = 0;
        Header(std::size_t l);
    };

    struct Pointer
    {
        const Header* header = nullptr;
        uint8_t*      data   = nullptr;
        Pointer(const Header* header, uint8_t* data);

        bool is_valid() const;

        operator bool() const;
    };

    StackMemoryPool() = default;
    StackMemoryPool(uint8_t* buffer, std::size_t len);

    void configure(uint8_t* buffer, std::size_t len);

    uint8_t* allocate(std::size_t n) override;
    void     deallocate(uint8_t* buffer, std::size_t n) override;

    // Stack Operations
    void    pop();
    Pointer emplace(std::size_t n);
    Pointer top();

private:
    const Header* get_header() const;

    uint8_t*    m_buffer    = nullptr;
    std::size_t m_len       = 0;
    std::size_t m_num_alloc = 0;
};
}  // namespace bte