///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in the
/// file 'LICENSE', which is part of this source code package.
///-----------------------------------------------------------------------------

#include "beetree/engine/stack-memory-pool.hpp"

#include <memory>

namespace bte {

StackMemoryPool::Header::Header(std::size_t l) : len(l) {}

StackMemoryPool::Pointer::Pointer(const Header* h, uint8_t* d) : header(h), data(d) {}

bool StackMemoryPool::Pointer::is_valid() const { return header != nullptr && data != nullptr; }

StackMemoryPool::Pointer::operator bool() const { return is_valid(); }

StackMemoryPool::StackMemoryPool(uint8_t* buffer, std::size_t len)
    : m_buffer(buffer), m_len(len), m_num_alloc(0)
{}

void StackMemoryPool::configure(uint8_t* buffer, std::size_t len)
{
    m_buffer    = buffer;
    m_len       = len;
    m_num_alloc = 0;
}

const StackMemoryPool::Header* StackMemoryPool::get_header() const
{
    const Header* header = nullptr;
    if (m_num_alloc >= sizeof(Header))
    {
        header = reinterpret_cast<Header*>(&m_buffer[m_num_alloc - sizeof(Header)]);
    }
    return header;
}

uint8_t* StackMemoryPool::allocate(std::size_t n)
{
    uint8_t*    buffer = nullptr;
    std::size_t total  = n + sizeof(Header);
    if (is_okay())
    {
        if (m_num_alloc + total <= m_len)
        {
            buffer = &m_buffer[m_num_alloc];
            m_num_alloc += total;

            // use new placement to call the constructor for the header
            Header* header = new (&buffer[n]) Header(n);
            ((void)header);  // swallow the result, no need to deallocate
                             // since its captured on the stack

            raise_allocated(total, m_num_alloc, m_len);
        }
        else
        {
            raise_error(MemoryPool::Flags::OutOfMemory);
        }
    }
    return buffer;
}

void StackMemoryPool::deallocate(uint8_t* buffer, std::size_t n)
{
    // make sure we are not corupted before attempting to deallocate
    if (!is_okay(MemoryPool::Flags::MemoryCorrupted))
    {
        return;
    }

    const Header* header = get_header();

    // deallocate if memory looks good
    if (header != nullptr && header->len == n)
    {
        std::size_t total_to_deallocate = n + sizeof(Header);
        if (total_to_deallocate <= m_num_alloc)
        {
            if (&m_buffer[m_num_alloc - total_to_deallocate] == buffer)
            {
                // call destructor on header
                header->~Header();
                // deallocate the memory
                m_num_alloc -= total_to_deallocate;
                raise_deallocated(total_to_deallocate, m_num_alloc, m_len);
            }
            else
            {
                raise_error(MemoryPool::Flags::MemoryCorrupted);
            }
        }
        else
        {
            raise_error(MemoryPool::Flags::MemoryCorrupted);
        }
    }
    else
    {
        raise_error(MemoryPool::Flags::MemoryCorrupted);
    }
}

StackMemoryPool::Pointer StackMemoryPool::emplace(std::size_t n)
{
    const Header* header = nullptr;
    uint8_t*      buff   = nullptr;

    if (n > 0)
    {
        buff = allocate(n);
        if (buff)
        {
            header = get_header();
        }
    }

    return Pointer(header, buff);
}

void StackMemoryPool::pop()
{
    Pointer p = top();
    if (p)
    {
        deallocate(p.data, p.header->len);
    }
}

StackMemoryPool::Pointer StackMemoryPool::top()
{
    uint8_t*      buff   = nullptr;
    const Header* header = get_header();

    if (header != nullptr)
    {
        std::size_t total = header->len + sizeof(Header);
        if (total <= m_num_alloc)
        {
            buff = &m_buffer[m_num_alloc - total];
        }
        else
        {
            header = nullptr;
            raise_error(MemoryPool::Flags::MemoryCorrupted);
        }
    }
    else if (m_num_alloc > 0)
    {
        raise_error(MemoryPool::Flags::MemoryCorrupted);
    }

    return Pointer(header, buff);
}
}  // namespace bte