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

#include "LayoutGenerator.hpp"
#include "Coordinates.hpp"
#include "Object.hpp"
#include "Tile.hpp"

namespace airball
{
namespace map
{

class Level
{
public:
    typedef std::multimap<Coordinates, SharedObjectPtr> ObjectMap;

    Level(unsigned width, unsigned height, unsigned uuid = 0);
    Level(unsigned width, unsigned height, LevelLayout&& layout, unsigned uuid = 0);

    unsigned uuid() const;

    Coordinates dimensions() const;
    const Tile& tile(const Coordinates& coord) const;

    bool addObject(const SharedCObjectPtr& object);
    void updateObject(const SharedCObjectPtr& object);
    void removeObject(const SharedCObjectPtr& object);
    void moveObject(const SharedCObjectPtr& object, const Coordinates& dest);

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

private:
    unsigned width_;
    unsigned height_;
    unsigned uuid_;

    LevelLayout layout_;
    ObjectMap objects_;
};

} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_LEVEL_HPP_
