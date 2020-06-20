//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once
#include <cstdint>
#include <utility>
#include "beetree/btos/flag-types.hpp"

namespace bte {
class MemoryPool
{
public:
    enum class Flags
    {
        OutOfMemory,
        MemoryCorrupted,
    };

    class Observer
    {
    protected:
        Observer() = default;

    public:
        virtual ~Observer() = default;

        virtual void on_error(MemoryPool::Flags reason){};
        virtual void on_allocated(std::size_t nalloc, std::size_t ntotal, std::size_t ncapacity) {}
        virtual void on_deallocated(std::size_t ndealloc,
                                    std::size_t ntotal,
                                    std::size_t ncapacity){};
    };

    MemoryPool()          = default;
    virtual ~MemoryPool() = default;

    // disable move semantics
    MemoryPool(MemoryPool&&) = delete;
    MemoryPool& operator=(MemoryPool&&) = delete;

    // disable copy semantics
    MemoryPool(const MemoryPool&) = delete;
    MemoryPool& operator=(const MemoryPool&) = delete;

    virtual uint8_t* allocate(std::size_t n)                    = 0;
    virtual void     deallocate(uint8_t* buffer, std::size_t n) = 0;

    void set_observer(Observer& obs);
    void set_observer(std::nullptr_t);

    bool is_okay() const;
    bool is_okay(MemoryPool::Flags flag) const;

protected:
    void raise_error(MemoryPool::Flags flag);
    void raise_allocated(std::size_t nalloc, std::size_t ntotal, std::size_t ncapacity);
    void raise_deallocated(std::size_t ndealloc, std::size_t ntotal, std::size_t ncapacity);

private:
    Observer*                     m_observer = nullptr;
    bte::Flags<MemoryPool::Flags> m_flags;
};
}  // namespace bte

// forward declaration
void* operator new(std::size_t nbytes, bte::MemoryPool& pool) noexcept;
