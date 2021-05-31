///-----------------------------------------------------------------------------
/// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE', which is part of this source code package.
///
/// @file 'C++' wrapper of a simple ring 'Q'. User of the ring 'Q' must be
/// knowledgeable with its shortcomings, i.e. it is not inherently robust.
///-----------------------------------------------------------------------------

#pragma once

#include <utility>
#include "platform-library/ring-q.h"

namespace platform
{
    ///
    /// C++ wrapper around the 'C' ringq.
    ///
    ///
    class RingQ
    {
    public:
        ///
        /// Construct a new Ring Q object
        ///
        /// @param buff the ring q buffer
        /// @param n the size of the buffer
        ///
        RingQ(uint8_t* buff, std::size_t n) { ringq_init(buff, n, &m_q); }

        ///
        /// Pop the oldest element from the ring Q and return its value.
        ///
        /// @note
        /// Invoking `pop()` is undefined when the Q contains 0 elements. It is
        /// the responsibility of the caller to check the size of the Q before invoking.
        ///
        /// @return uint8_t the value of the popped element from the ring Q
        ///
        uint8_t pop() { return ringq_pop(&m_q); }

        ///
        /// Push the given `byte` onto the ring queue.
        ///
        /// @note
        /// Invoking `ringq_push()` is undefined when the number of elementes in the Q
        /// is greater than or equal to it's capacity. It is the responsibility of the
        /// caller to check the size of the Q against it's capacity before invoking.
        ///
        /// @param byte the value to push onto the ring 'Q'
        ///
        void push(uint8_t byte) { ringq_push(&m_q, byte); }

        ///
        /// @return the number of elements currently in the ring 'Q'
        ///
        std::size_t count() const { return ringq_count(&m_q); }

        ///
        /// @param q  the ring Q context
        /// @return the ring Q's capacity, i.e. the size of the underlying buffer
        ///
        std::size_t capacity() const { return ringq_capacity(&m_q); }

    private:
        RingQ_t m_q;
    };

    ///
    /// Container for declaring both the RingQ and it's buffer.
    ///
    /// Usage:
    /// @code
    /// RingQContainer<512> q; // create a ringq of 512 bytes
    ///
    /// q->push(4); // push an element on the queue using the member pointer access operator
    /// while(q->count()) { q->pop(); }
    ///
    /// pass_to_a_func(*q); // dereference to access RingQ& to pass to a function, e.g. void pass_to_a_func(RingQ& q);
    /// @endcode
    ///
    /// @tparam N the size of the ring Q allocated at compile time.
    ///
    template <std::size_t N>
    class RingQContainer
    {
    public:
        RingQ* operator->() { return &m_q; }
        RingQ& operator*() { return m_q; }

    private:
        uint8_t m_buff[N];
        RingQ m_q{m_buff, N};
    };
}  // namespace platform
