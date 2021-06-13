//------------------------------------------------------------------------------
// Copyright (C) 2020 The BeeTree Authors - All Rights Reserved
//
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#include "beetree/engine/stack.hpp"
#include <memory>

namespace bte {
class NodePointer
{
public:
    const Node* value;

    NodePointer(const Node& v) : value(&v) {}
};

void Stack::configure(uint8_t* buffer, std::size_t len) { m_mem_pool.configure(buffer, len); }

Stack::~Stack()
{
    while (!empty())
    {
        pop();
    }
}

const Element& Stack::top() const { return m_top; }

Element Stack::pointer_to_element(const StackMemoryPool::Pointer& p)
{
    Element e;
    if (p)
    {
        NodePointer* node = reinterpret_cast<NodePointer*>(&p.data[0]);

        uint8_t* data     = nullptr;
        int32_t  data_len = p.header->len - sizeof(NodePointer);
        if (data_len > 0)
        {
            data = &p.data[sizeof(NodePointer)];
        }

        e = Element(node->value, data, data_len);
    }
    return e;
}

void Stack::pop()
{
    m_mem_pool.pop();
    m_top = pointer_to_element(m_mem_pool.top());
}

bool Stack::empty() { return !m_mem_pool.top(); }

bool Stack::push(const Node& node, std::size_t data_len)
{
    bool                     allocated = false;
    StackMemoryPool::Pointer p         = m_mem_pool.emplace(sizeof(NodePointer) + data_len);

    if (p)
    {
        // store a pointer of the node on to the allocated data
        NodePointer* np = new (&p.data[0]) NodePointer(node);
        ((void)np);  // swallow result

        m_top = pointer_to_element(p);

        allocated = true;
    }

    return allocated;
}

}  // namespace bte