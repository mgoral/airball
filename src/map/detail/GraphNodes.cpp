/**
 * Copyright (C) Michal Goral, 2014
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "GraphNodes.hpp"

//
// Node
//

namespace airball
{
namespace map
{
namespace detail
{

bool operator==(const Node& lhs, const Node& rhs)
{
    return (lhs.coordinates() == rhs.coordinates());
}

bool operator<(const Node& lhs, const Node& rhs)
{
    return (lhs.coordinates() < rhs.coordinates());
}

std::size_t hash_value(const Node& node)
{
    return hash_value(node.coordinates());
}

std::size_t hash_value(const NodeCPtr& nodePtr)
{
    return hash_value(*nodePtr);
}

//
// HeapNode
//

bool operator==(const HeapNode& lhs, const HeapNode& rhs)
{
    return (lhs.node() == rhs.node());
}

bool operator<(const HeapNode& lhs, const HeapNode& rhs)
{
    // std provides only a max heap but we want a min heap in A* implementation so we have
    // to cheat a little.
    return (lhs.cost() > rhs.cost());
}

bool operator<(const HeapNodePtr& lhs, const HeapNodePtr& rhs)
{
    return *lhs < *rhs;
}

} // namespace detail
} // namespace map
} // namespace airball
