//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/btos/memory.hpp"
#include "beetree/btos/flags.hpp"

namespace bte {

void MemoryPool::set_observer(MemoryPool::Observer& obs) { m_observer = &obs; }

void MemoryPool::set_observer(std::nullptr_t) { m_observer = nullptr; }

bool MemoryPool::is_okay() const { return flags::none(m_flags); }

bool MemoryPool::is_okay(MemoryPool::Flags flag) const { return !flags::test(m_flags, flag); }

void MemoryPool::raise_error(MemoryPool::Flags reason)
{
    bool changed = flags::set(m_flags, reason);
    if (m_observer != nullptr && changed)
    {
        m_observer->on_error(reason);
    }
}

void MemoryPool::raise_allocated(std::size_t nalloc, std::size_t ntotal, std::size_t ncapacity)
{
    if (m_observer != nullptr)
    {
        m_observer->on_allocated(nalloc, ntotal, ncapacity);
    }
}
void MemoryPool::raise_deallocated(std::size_t ndealloc, std::size_t ntotal, std::size_t ncapacity)
{
    if (m_observer != nullptr)
    {
        m_observer->on_deallocated(ndealloc, ntotal, ncapacity);
    }
}
}  // namespace bte

void* operator new(std::size_t nbytes, bte::MemoryPool& pool) noexcept
{
    if (nbytes <= 0) nbytes = sizeof(void*);
    return pool.allocate(nbytes);
}
