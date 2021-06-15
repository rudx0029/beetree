//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------
#pragma once

#include "beetree/engine/node.hpp"
#include "beetree/engine/stack-memory-pool.hpp"

namespace bte {
struct Element
{
    const Node* node = nullptr;
    uint8_t*    data = nullptr;
    std::size_t len  = 0;

    Element() = default;
    Element(const Node* n, uint8_t* d, std::size_t l) : node(n), data(d), len(l) {}

    bool is_valid() const { return node != nullptr && node->build != nullptr; }
         operator bool() const { return is_valid(); }
};

class Stack
{
public:
    Stack() = default;
    ~Stack();

    void configure(uint8_t* buffer, std::size_t len);

    ///
    /// @return Element the top most element in the stack
    /// @return an invalid element when the stack is empty
    ///
    const Element& top() const;

    ///
    /// @return true when the stack is empty
    /// @return false otherwise
    ///
    bool empty();

    ///
    /// Pushes the node onto the stack and allocates memory for the nodes
    /// state data
    ///
    /// @param node the node
    /// @param data_len the length of the node's state data.
    /// @return true the node is pushed onto the stack and the state data is
    /// allocated
    /// @return false otherwise
    ///
    bool push(const Node& node, std::size_t data_len);

    ///
    /// Pops the top of the stack off, removing the top node and
    /// deallocating the state data
    ///
    void pop();

private:
    Element pointer_to_element(const StackMemoryPool::Pointer& p);

    StackMemoryPool m_mem_pool;
    Element         m_top;
};

}  // namespace bte
