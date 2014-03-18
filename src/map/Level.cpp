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

#include <functional>
#include <algorithm>

#include "Level.hpp"
#include "ObjectPredicates.hpp"

namespace airball
{
namespace map
{

Level::Level(unsigned width, unsigned height, unsigned uuid) :
    width_(width), height_(height), uuid_(uuid),
    layout_(width_, std::vector<Tile>(height_, Tile("empty")))
{
}

Coordinates Level::dimensions() const
{
    return Coordinates(width_, height_);
}

const Tile& Level::tile(const Coordinates& coord) const
{
    return layout_.at(coord.x).at(coord.y);
}

bool Level::addObject(const SharedCObjectPtr& object)
{
    if (objectCanBeAdded(object, object->coordinates()))
    {
        objects_.insert(std::make_pair(object->coordinates(), object->clone()));
        return true;
    }

    return false;
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
            return;
        }
    }
}

void Level::moveObject(const SharedCObjectPtr& object, const Coordinates& dest)
{
    if (objectCanBeAdded(object, dest))
    {
        ObjectMap::const_iterator searchIt = findObject(object);
        if (searchIt != objects_.end())
        {
            SharedObjectPtr objectToMove = searchIt->second;
            objectToMove->changeCoordinates(dest);

            objects_.erase(searchIt);
            objects_.insert(std::make_pair(dest, objectToMove));
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
    using namespace std::placeholders;
    std::function<bool(const Object&)> pred = std::bind(&pred::hasCoordinates, _1, coord);
    return findObjects(pred);
}

std::vector<SharedCObjectPtr> Level::objectsAt(const Coordinates& from, const Coordinates& to) const
{
    using namespace std::placeholders;
    std::function<bool(const Object&)> pred = std::bind(&pred::hasCoordinatesInRange, _1, from, to);
    return findObjects(pred);
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

bool Level::objectCanBeAdded(const SharedCObjectPtr& obj, const Coordinates& coord) const
{
    // Object cannot be added:
    // - on tiles that are obstacles
    // - on obstacles and creatures when it's obstacle or creature itself

    if (!tile(coord).isObstacle())
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

Level::ObjectMap::const_iterator Level::findObject(const SharedCObjectPtr& object) const
{
    using namespace std::placeholders;

    std::pair<ObjectMap::const_iterator, ObjectMap::const_iterator> boundaries =
        objects_.equal_range(object->coordinates());

    ObjectMap::const_iterator searchIt = std::find_if(boundaries.first, boundaries.second,
        [&](const ObjectMap::value_type& val) -> bool
        { return pred::hasUuid(*val.second, object->uuid()); });

    // Callers of this method do not know anything about boundaries
    if (searchIt == boundaries.second)
        return objects_.end();
    return searchIt;
}

} // namespace map
} // namespace airball
