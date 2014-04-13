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

#ifndef AIRBALL_MAP_LEVEL_HPP_
#define AIRBALL_MAP_LEVEL_HPP_

#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <stdexcept>

#include "MapTypes.hpp"
#include "LayoutGenerator.hpp"
#include "Coordinates.hpp"
#include "Object.hpp"
#include "Tile.hpp"
#include "LevelGraph.hpp"

namespace airball
{
namespace map
{

class Level
{
public:
    typedef std::multimap<Coordinates, SharedObjectPtr> ObjectMap;

    Level(unsigned width, unsigned height, unsigned uuid = 0);
    Level(LevelLayout&& layout, unsigned uuid = 0);

    unsigned uuid() const;

    Coordinates dimensions() const;
    const Tile& tile(const Coordinates& coord) const;
    const LevelLayout& layout() const;

    /**
     * Add, update or remove an object. Where appliable, the method will perform object copy, so a
     * given Object pointer WILL NOT point to the stored object.
     */
    bool addObject(const SharedCObjectPtr& object);
    void updateObject(const SharedCObjectPtr& object);
    void removeObject(const SharedCObjectPtr& object);

    /**
     * Move object towards destination. If objects' current moving path ends on different
     * destination, a new moving path will be calculated and stored before the movement occurs.
     */
    void moveObject(const SharedCObjectPtr& object, const Coordinates& dest);

    /**
     * Set shortest moving path towards destination for the object, but DO NOT move it.
     * Usually it's used to store moving path for the player to draw it later.
     */
    void setObjectDestination(const SharedCObjectPtr& object, const Coordinates& dest);

    /**
     * Access stored objects:
     *   + all objects
     *   + at given coordinates
     *   + at coordinates meeting criteria: from <= coordinates < to
     *   + all objects meeting a given predicate
     */
    std::vector<SharedCObjectPtr> objects() const;
    std::vector<SharedCObjectPtr> objectsAt(const Coordinates& coord) const;
    std::vector<SharedCObjectPtr> objectsAt(const Coordinates& from, const Coordinates& to) const;
    std::vector<SharedCObjectPtr> findObjects(std::function<bool(const Object&)> pred) const;

    template<typename T>
    T& accessObjectComponent(const SharedCObjectPtr& object)
    {
        ObjectMap::iterator searchIt = findObject(object);
        if (searchIt != objects_.end())
            return searchIt->second->getComponent<T>();
        throw std::invalid_argument("Object not found: " + std::to_string(object->uuid()));
    }

    Path shortestPath(const Coordinates& from, const Coordinates& to) const;

    friend bool operator==(const Level& lhs, const Level& rhs)
    {
        return (lhs.uuid_ == rhs.uuid_);
    }

    friend bool operator!=(const Level& lhs, const Level& rhs)
    {
        return !(lhs == rhs);
    }

private:
    bool objectCanBeAdded(const SharedCObjectPtr& obj, const Coordinates& coord) const;
    ObjectMap::iterator findObject(const SharedCObjectPtr& object);
    ObjectMap::const_iterator findObject(const SharedCObjectPtr& object) const;

    template <typename Iterator, typename T>
    static Iterator findObjectImpl(T This, const SharedCObjectPtr& object);

    /**
     * Recalculate Movement Cost Map (MCM).
     * On MCM movement cost through obstacles is infinity (they're not removed from graph because
     * some obstacles (e.g. creatures) might move and we'd have to regenerate graph on each move).
     *
     * Note that some creatures might not be obstacles (like friendly creatures?) and there is no
     * cost in moving through them.
     */
    void calculateMovementCostMap();

    /**
     * Calculate moving path for object to destination coordinates.
     * Moving path is the shortest path to destination as calculated by LevelGraph path finding
     * algorithm.
     *
     * It is possible to move towards obstacle objects (like creatures - user may click on them)
     * which have infinite cost move, but it's impossible to move towards obstacle tiles (like
     * walls). Walls are removed from graph anyway, so LevelGraph would throw an exception in that
     * case.
     */
    void setObjectDestinationImpl(SharedObjectPtr& object, const Coordinates& dest);

private:
    unsigned width_;
    unsigned height_;
    unsigned uuid_;

    LevelLayout layout_;
    ObjectMap objects_;

    LevelGraph levelGraph_;
    CostMap movementCostMap_;
};

} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_LEVEL_HPP_
