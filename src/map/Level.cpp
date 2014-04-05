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

#include <stdexcept>
#include <functional>
#include <algorithm>

#include "Level.hpp"
#include "ObjectPredicates.hpp"
#include "LayoutGenerator.hpp"
#include "CostCalculator.hpp"

namespace airball
{
namespace map
{

Level::Level(LevelLayout&& layout, unsigned uuid) :
    width_(layout.size()), height_(layout.at(0).size()), uuid_(uuid), layout_(std::move(layout)),
    levelGraph_(layout_)
{
    calculateMovementCostMap();
}

Level::Level(unsigned width, unsigned height, unsigned uuid) :
    Level(LevelLayout(width, std::vector<Tile>(height, Tile("floor.png"))), uuid)
{
}

unsigned Level::uuid() const
{
    return uuid_;
}

Coordinates Level::dimensions() const
{
    return Coordinates(width_, height_);
}

const Tile& Level::tile(const Coordinates& coord) const
{
    return layout_[coord.x][coord.y];
}

const LevelLayout& Level::layout() const
{
    return layout_;
}

bool Level::addObject(const SharedCObjectPtr& object)
{
    if (objectCanBeAdded(object, object->coordinates()))
    {
        objects_.insert(std::make_pair(object->coordinates(), object->clone()));

        if (pred::isObstacle(*object))
            calculateMovementCostMap();

        return true;
    }

    return false;
}

void Level::updateObject(const SharedCObjectPtr& object)
{
    ObjectMap::iterator searchIt = findObject(object);
    if (searchIt != objects_.end())
    {
        searchIt->second = std::move(object->clone());
    }
}

void Level::removeObject(const SharedCObjectPtr& object)
{
    std::pair<ObjectMap::iterator, ObjectMap::iterator> boundaries =
        objects_.equal_range(object->coordinates());
    ObjectMap::iterator objectIt = boundaries.first;

    for (; objectIt != boundaries.second; ++objectIt)
    {
        if (pred::hasUuid(*(objectIt->second), object->uuid()))
        {
            objects_.erase(objectIt);

            if (pred::isObstacle(*object))
                calculateMovementCostMap();

            return;
        }
    }
}

void Level::setObjectDestination(const SharedCObjectPtr& object, const Coordinates& dest)
{
    ObjectMap::const_iterator searchIt = findObject(object);
    if (searchIt != objects_.end())
    {
        SharedObjectPtr objectToMove = searchIt->second;
        setObjectDestinationImpl(objectToMove, dest);
    }
}

void Level::moveObject(const SharedCObjectPtr& object, const Coordinates& dest)
{
    ObjectMap::const_iterator searchIt = findObject(object);
    if (searchIt != objects_.end())
    {
        SharedObjectPtr objectToMove = searchIt->second;
        setObjectDestinationImpl(objectToMove, dest);

        if (!objectToMove->movingPath().empty() &&
            objectCanBeAdded(objectToMove, objectToMove->nextStep()))
        {
            objectToMove->moveBySingleStep();

            objects_.erase(searchIt);
            objects_.insert(std::make_pair(objectToMove->coordinates(), objectToMove));

            calculateMovementCostMap();
        }
    }
}

std::vector<SharedCObjectPtr> Level::objects() const
{
    std::vector<SharedCObjectPtr> ret;
    std::transform(objects_.begin(), objects_.end(), std::back_inserter(ret),
        [](const ObjectMap::value_type& val) { return val.second; });
    return ret;
}

std::vector<SharedCObjectPtr> Level::objectsAt(const Coordinates& coord) const
{
    std::vector<SharedCObjectPtr> ret;
    std::pair<ObjectMap::const_iterator, ObjectMap::const_iterator> boundaries =
        objects_.equal_range(coord);

    std::transform(boundaries.first, boundaries.second, std::back_inserter(ret),
        [](const ObjectMap::value_type& val) { return val.second; });

    return ret;
}

std::vector<SharedCObjectPtr> Level::objectsAt(const Coordinates& from, const Coordinates& to) const
{
    std::vector<SharedCObjectPtr> ret;

    ObjectMap::const_iterator fromIt = objects_.lower_bound(from);
    ObjectMap::const_iterator toIt = objects_.upper_bound(to);

    std::transform(fromIt, toIt, std::back_inserter(ret),
        [](const ObjectMap::value_type& val) { return val.second; });

    return ret;
}

std::vector<SharedCObjectPtr> Level::findObjects(std::function<bool(const Object&)> pred) const
{
    std::vector<SharedCObjectPtr> ret;
    for (const ObjectMap::value_type& val : objects_)
    {
        if (pred(*val.second))
            ret.push_back(val.second);
    }
    return ret;
}

Path Level::shortestPath(const Coordinates& from, const Coordinates& to) const
{
    return levelGraph_.findPath(from, to, movementCostMap_);
    //return levelGraph_.findDijkstraPath(from, to, movementCostMap_);
}

bool Level::objectCanBeAdded(const SharedCObjectPtr& obj, const Coordinates& coord) const
{
    // Object cannot be added:
    // - when destination is not in layout boundaries
    // - on tiles that are obstacles
    // - on obstacles and creatures when it's obstacle or creature itself

    if (!coord.inBoundaries(layout_) || !tile(coord).isObstacle())
    {
        if (!pred::isObstacle(*obj) && !pred::isCreature(*obj))
            return true;

        std::pair<ObjectMap::const_iterator, ObjectMap::const_iterator> boundaries =
            objects_.equal_range(coord);

        ObjectMap::const_iterator obstacleObjIt = std::find_if(boundaries.first, boundaries.second,
            [](const ObjectMap::value_type& val) -> bool
            { return (pred::isObstacle(*val.second) || pred::isCreature(*val.second)); });

        return (obstacleObjIt == boundaries.second);
    }

    return false;
}

Level::ObjectMap::iterator Level::findObject(const SharedCObjectPtr& object)
{
    return findObjectImpl<ObjectMap::iterator>(this, object);
}

Level::ObjectMap::const_iterator Level::findObject(const SharedCObjectPtr& object) const
{
    return findObjectImpl<ObjectMap::const_iterator>(this, object);
}

// Yeah, I hate code duplication THAT much :)
template <typename Iterator, typename T>
Iterator Level::findObjectImpl(T This, const SharedCObjectPtr& object)
{
    using namespace std::placeholders;

    std::pair<Iterator, Iterator> boundaries = This->objects_.equal_range(object->coordinates());

    Iterator searchIt = std::find_if(boundaries.first, boundaries.second,
        [&](const ObjectMap::value_type& val) -> bool
        { return pred::hasUuid(*val.second, object->uuid()); });

    // Callers of this method do not know anything about boundaries
    if (searchIt == boundaries.second)
        return This->objects_.end();
    return searchIt;
}

void Level::calculateMovementCostMap()
{
    std::vector<SharedCObjectPtr> obstacles = findObjects(
        [](const Object& obj) { return (pred::isObstacle(obj)); });

    GoalList obstacleCoords;
    std::transform(obstacles.begin(), obstacles.end(), std::back_inserter(obstacleCoords),
        [](const SharedCObjectPtr& obj) -> Coordinates { return obj->coordinates(); });

    CostCalculator costCalculator;
    movementCostMap_ = costCalculator.calculate(GoalList(), obstacleCoords, layout());
}

void Level::setObjectDestinationImpl(SharedObjectPtr& object, const Coordinates& dest)
{
    if (object->coordinates() == dest)
    {
        object->clearPath();
        return;
    }

    if (dest.inBoundaries(layout_) && !layout_[dest.x][dest.y].isObstacle())
    {
        const Path& currentMovingPath = object->movingPath();
        if (currentMovingPath.empty() || currentMovingPath[0] != dest)
        {
            Path movingPath;
            if (object->coordinates().isNeighbour(dest))
            {
                // No need to run path finding for neighbours ;)
                movingPath.push_back(dest);
            }
            else
            {
                movingPath = shortestPath(object->coordinates(), dest);
            }
            object->setMovingPath(movingPath);
        }
    }
}

} // namespace map
} // namespace airball
