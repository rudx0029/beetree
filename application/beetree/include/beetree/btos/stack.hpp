//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include <cstdint>
#include <utility>

namespace bte {
template <class T>
class Stack final
{
public:
    Stack(T* stack, std::size_t capacity) : m_stack(stack), m_capacity(capacity) {}

    ///
    /// Pushes an element on to the stack using perfect forwarding.
    ///
    /// @note
    /// Call Stack<T>::full prior to calling push to check if the stack is
    /// not at capacity. The behavior is undefined if pushing an item on a
    /// stack at capacity.
    ///
    /// @tparam FORWARD perfect forwarding type
    /// @param item the item to push onto the stack
    ///
    template <class FORWARD>
    void push(FORWARD&& item)
    {
        m_stack[m_size] = std::forward<T>(item);
        m_size++;
    }
    ///
    /// Pops the top item off the stack
    ///
    void pop()
    {
        if (m_size != 0) m_size--;
    }
    ///
    /// Clears the stack
    ///
    void clear() { m_size = 0; }
    ///
    /// Retrieves a read only reference to the top of the stack.
    ///
    /// @note Call Stack<T>::empty prior to check if an element exists. The
    /// behavior is undefined if the stack is empty.
    ///
    /// @return read only reference to the top of the stack
    ///
    const T& top() const { return m_stack[m_size - 1]; }
    ///
    /// Retrieves a modifiable reference to the top of the stack.
    ///
    /// @note Call Stack<T>::empty prior to check if an element exists. The
    /// behavior is undefined if the stack is empty.
    ///
    /// @return modifiable reference to the top of the stack
    ///
    T& top() { return m_stack[m_size - 1]; }
    ///
    /// @return true when the stack is at capacity
    /// @return false otherwise
    ///
    bool full() const { return m_size >= m_capacity; }
    ///
    /// @return true when the stack is empty
    /// @return false otherwise
    ///
    bool empty() const { return m_size == 0; }
    ///
    /// @return the number of items in the stack
    ///
    std::size_t size() const { return m_size; }

private:
    T*          m_stack    = nullptr;
    std::size_t m_capacity = 0;
    std::size_t m_size     = 0;
};

template <class T, std::size_t CAPACITY>
class StackContainer
{
public:
    Stack<T>&       stack() { return m_stack; }
    const Stack<T>& stack() const { return m_stack; }

    const Stack<T>* operator->() const { return &m_stack; }
    Stack<T>*       operator->() { return &m_stack; }

    const Stack<T>& operator*() const { return m_stack; }
    Stack<T>&       operator*() { return m_stack; }

private:
    T        m_buffer[CAPACITY];
    Stack<T> m_stack{m_buffer, CAPACITY};
};
}  // namespace bte