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

#include <cstdlib>
#include <algorithm>
#include <string>
#include <functional>
#include <utility>
#include <boost/assert.hpp>
#include <boost/functional/hash.hpp>

#include "LevelGraph.hpp"

#include "detail/Utils.hpp"

namespace airball
{
namespace map
{

LevelGraph::LevelGraph(const LevelLayout& layout)
{
    reset(layout);
}

void LevelGraph::reset(const LevelLayout& layout)
{
    // Note for future implementations: just make this method public and call it whenever
    // LevelLayout changes.
    graph_.clear();

    int x = 0;
    for (; x < static_cast<int>(layout.size()); ++x)
    {
        int y = 0;
        for (; y < static_cast<int>(layout.at(x).size()); ++y)
        {
            addNode(x, y, layout);
        }
    }
}

Path LevelGraph::findPath(const Coordinates& from, const Coordinates& to,
    const CostMap& costMap) const
{
    return findPath(findNode(from), findNode(to), costMap, diagonalShortcutHeuristic);
}

Path LevelGraph::findDijkstraPath(const Coordinates& from, const Coordinates& to,
    const CostMap& costMap) const
{
    return findPath(findNode(from), findNode(to), costMap, dijkstraHeuristic);
}

airball::map::detail::NodePtr& LevelGraph::insertNode(const Coordinates& coord, const NodePtr& node)
{
    std::pair<NodeMap::iterator, bool> ret = graph_.insert(std::make_pair(coord, node));
    return ret.first->second;
}

void LevelGraph::addNode(int x, int y, const LevelLayout& layout)
{
    BOOST_ASSERT_MSG(x >= 0, "LevelGraph: cannot add node with negative 'x' coordinate");
    BOOST_ASSERT_MSG(y >= 0, "LevelGraph: cannot add node with negative 'y' coordinate");

    if (!layout.at(x).at(y).isObstacle())
    {
        Coordinates coord(x, y);
        NodePtr node = insertNode(coord, std::make_shared<Node>(coord));
        addNodeNeighbours(layout, node);
    }
}

void LevelGraph::addNodeNeighbours(const LevelLayout& layout, NodePtr& node)
{
    int x = node->coordinates().x;
    int y = node->coordinates().y;

    // scan all available tiles around (x, y) coordinates.
    int xx = std::max(0, x - 1);
    int xxEnd = std::min(static_cast<int>(layout.size()), x + 2);

    for (; xx < xxEnd; ++xx)
    {
        int yy = std::max(0, y - 1);
        int yyEnd = std::min(static_cast<int>(layout.at(xx).size()), y + 2);

        for (; yy < yyEnd; ++yy)
        {
            if (!(xx == x && yy == y) && !layout.at(xx).at(yy).isObstacle())
            {
                Coordinates coord(xx, yy);
                NodePtr neighbour = insertNode(coord, std::make_shared<Node>(coord));
                node->addNeighbour(neighbour);
            }
        }
    }
}

const airball::map::detail::NodePtr& LevelGraph::findNode(const Coordinates& coord) const
{
    NodeMap::const_iterator it = graph_.find(coord);
    if (it != graph_.end())
    {
        return it->second;
    }

    throw std::logic_error("Node not found in graph: " +
            std::to_string(coord.x) + ", " + std::to_string(coord.y));
}

template <typename HeuristicFunc>
Path LevelGraph::findPath(const NodePtr& startNode, const NodePtr& goalNode, const CostMap& costMap,
    HeuristicFunc heuristic) const
{
    SearchMap nodeSearchMap;
    std::vector<HeapNodePtr> openNodes; // priority queue [max heap - but we have a special
                                        // operator<() for HeapNode ;)]

    HeapNodePtr start = std::make_shared<HeapNode>(startNode);
    start->setDistance(0);
    start->setCost(heuristic(startNode, startNode, goalNode));
    start->setState(detail::NodeStateOpen);

    nodeSearchMap.insert(std::make_pair(startNode, start));
    openNodes.push_back(start);

    // implemented on Boost A* algorithm:
    // http://www.boost.org/doc/libs/1_38_0/libs/graph/doc/astar_search.html
    unsigned i = 0;
    while (!(openNodes.empty()))
    {
        ++i;
        HeapNodePtr heapCurrent = openNodes.front();
        std::pop_heap(openNodes.begin(), openNodes.end());
        openNodes.pop_back();

        if (heapCurrent->node() == goalNode)
            break;

        for (const NodeCPtr& neighbour : heapCurrent->node()->neighbours())
        {
            const Coordinates& coord = neighbour->coordinates();
            unsigned distance = costMap[coord.x][coord.y] + heapCurrent->distance();
            HeapNodePtr heapNeighbour = insertNodeToSearchMap(neighbour, nodeSearchMap);

            if (distance < heapNeighbour->distance())
            {
                heapNeighbour->setDistance(distance);
                heapNeighbour->setCost(
                    distance + heuristic(heapNeighbour->node(), startNode, goalNode));
                heapNeighbour->setParent(heapCurrent);

                if (heapNeighbour->state() != detail::NodeStateOpen)
                {
                    heapNeighbour->setState(detail::NodeStateOpen);
                    openNodes.push_back(heapNeighbour);
                    std::push_heap(openNodes.begin(), openNodes.end());
                }
                else
                {
                    std::vector<HeapNodePtr>::iterator it =
                        std::find(openNodes.begin(), openNodes.end(), heapNeighbour);
                    BOOST_ASSERT(it != openNodes.end()); // if heapNode.state == NodeStateOpen,
                                                         // it MUST be in openNodes heap
                    std::push_heap(openNodes.begin(), it + 1);
                }
            }
        }

        heapCurrent->setState(detail::NodeStateClosed);
    }

    return recreatePath(goalNode, nodeSearchMap);
}

Path LevelGraph::recreatePath(const NodePtr& goalNode, SearchMap& searchMap) const
{
    Path ret;

    // First heapNode points the goal. If no path was found (i.e. goal doesn't have a parent,
    // we'll return an empty path.
    HeapNodePtr heapNode = insertNodeToSearchMap(goalNode, searchMap);
    if (!heapNode->parent())
        return ret;

    while (heapNode)
    {
        ret.push_back(heapNode->node()->coordinates());
        heapNode = heapNode->parent();
    }

    return ret;
}

airball::map::detail::HeapNodePtr LevelGraph::insertNodeToSearchMap(const NodeCPtr& node,
    SearchMap& searchMap) const
{
    SearchMapRet ret = searchMap.insert(std::make_pair(node, std::make_shared<HeapNode>(node)));
    return ret.first->second;
}

unsigned LevelGraph::diagonalShortcutHeuristic(const NodeCPtr& node, const NodeCPtr&,
        const NodeCPtr& goal)
{
    Coordinates coord = node->coordinates() - goal->coordinates();
    coord.x = std::abs(coord.x);
    coord.y = std::abs(coord.y);

    if (coord.x > coord.y)
        return 14 * coord.y + 10 * (coord.x - coord.y);
    else
        return 14 * coord.x + 10 * (coord.y - coord.x);
}

unsigned LevelGraph::manhattanHeuristic(const NodeCPtr& node, const NodeCPtr&, const NodeCPtr& goal)
{
    Coordinates coord = node->coordinates() - goal->coordinates();
    const unsigned minimumMoveCost = 1;
    return minimumMoveCost * std::abs(coord.x) + std::abs(coord.y);
}

unsigned LevelGraph::dijkstraHeuristic(const NodeCPtr&, const NodeCPtr&, const NodeCPtr&)
{
    return 0;
}

} // namespace map
} // namespace airball
