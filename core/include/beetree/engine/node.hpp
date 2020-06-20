//------------------------------------------------------------------------------
// This file is subject to the terms and conditions defined in the
// file 'LICENSE', which is part of this source code package.
//------------------------------------------------------------------------------

#pragma once

#include <utility>
#include "beetree/engine/delegates.hpp"

namespace bte {

struct Recipe;  // forward declaration
struct Node;    // forward declaration

///
/// Fixed sized container for branches.
///
/// @tparam N The number of branches
///
template <std::size_t N>
struct Branches final
{
    constexpr std::size_t size() const { return N; }
    const Node*           branches[N];
};

///
/// A Node in Beetree contains a reference to its run-time build function and its child branches.
/// This allows the node be stored in read only memory, e.g FLASH, and consequently the entire
/// behavior tree to be stored in ROM. This achieves a small RAM footprint enabling the behavior
/// tree for embedded enviornments.
///
///
struct Node final
{
    using const_iterator = Node const* const*;

    /// A reference to the run-time build function
    delegate::Build build;
    /// A reference to a child branches for use as a Decorator
    const Node* branch;
    /// A reference to 1 or more child branches for use as a Composite
    const Node* const* branches;
    /// The number of branches the node has when used as a Composite
    const std::size_t num_branches;

    ///
    /// Constructor for representing a Leaf node
    /// @param b    a reference to the run-time build function
    ///
    constexpr Node(delegate::Build b)
        : build(b), branch(nullptr), branches(nullptr), num_branches(0)
    {}

    ///
    /// Constructor for representing a Decorator node
    /// @param b    a reference to the run-time build function
    /// @param br   a reference to the child branch
    ///
    constexpr Node(delegate::Build b, const Node& br)
        : build(b), branch(&br), branches(nullptr), num_branches(0)
    {}

    ///
    /// Constructor for representing a Composite node
    /// @param b    a reference to the run-time build function
    /// @param br   a reference to 1 or more child branches.
    /// @tparam N   the number of child branches
    ///
    template <std::size_t N>
    constexpr Node(delegate::Build b, const Branches<N>& br)
        : build(b), branch(nullptr), branches(br.branches), num_branches(br.size())
    {}
};

///
/// Leaf Node
/// =========
///
/// Wraps a node intended for a leaf. Use the Leaf Node over using Node directly as it improves
/// readability and specifies the nodes intentions.
///
/// Usage
/// -----
///
/// ```cpp
/// using ToggleDebugLED = Leaf<make_toggle_debug_led>;
/// constepxr ToggleDebugLED toggleLED;
/// ```
/// @tparam BuildNode  a reference to the run-time build function
///
template <delegate::Build BuildNode>
struct Leaf
{
    const Node node;

    constexpr Leaf() : node(BuildNode) {}

    constexpr operator const Node&() const { return node; }
};

///
/// Decorator Node
/// ==============
///
/// Wraps a node intended for a decorator. Use the Decorator Node over using Node directly as it
/// improves readability and specifies the nodes intentions.
///
/// Usage
/// -----
///
/// ```cpp
/// using Inverter = Decorator<make_inverter>;
/// constepxr auto invert = Inverter{childBranch};
/// ```
///
/// @tparam BuildNode  a reference to the run-time build function
///
template <delegate::Build BuildNode>
struct Decorator final
{
    const Node node;

    constexpr Decorator(const Node& branch) : node(BuildNode, branch) {}

    constexpr operator const Node&() const { return node; }
};

///
/// Composite Node
/// ==============
///
/// Wraps a node intended for a composite. Use the Composite Node over using Node directly as it
/// improves readability and specifies the nodes intentions.
///
/// Usage
/// -----
///
/// ```cpp
/// using Sequence = Composite<make_sequence>;
///
/// constexpr auto sequenceBranches = branches(nodeA, nodeB, nodeC);
/// constepxr auto sequence = Sequence{sequenceBranches};
/// ```
///
/// @tparam BuildNode  a reference to the run-time build function
///
template <delegate::Build BuildNode>
struct Composite final
{
    template <std::size_t N>
    constexpr Composite(const Branches<N>& branches) : node(BuildNode, branches)
    {}

    const Node node;

    constexpr operator const Node&() const { return node; }
};

///
/// Helper method to cast a Leaf, Decorator, Composite to a Node
///
/// @tparam T the source type
/// @param t the object to cast to a Node
/// @return constexpr const Node&
///
template <class T>
constexpr const Node& meta_cast(const T& t)
{
    return static_cast<const Node&>(t);
}

///
/// branches
/// ========
///
/// Constructs a set of Nodes into a Branches container to be referenced by a Composite.
///
/// Usage
/// -----
///
/// ```cpp
/// // create the branches container in ROM
/// constexpr auto childBranches = branches(nodeA, nodeB, nodeC)
/// // pass a reference of the container to a Composite
/// constexpr auto aComposite = Composite<make_something>(childBranches);
/// ```
///
/// @tparam Args Args of type Node
/// @param values the child branches
/// @return Branches<sizeof...(Args)>
///
template <typename... Args>
constexpr auto branches(const Args&... values) -> Branches<sizeof...(Args)>
{
    return Branches<sizeof...(Args)>{std::forward<const Node*>(&meta_cast<Args>(values))...};
}
}  // namespace bte