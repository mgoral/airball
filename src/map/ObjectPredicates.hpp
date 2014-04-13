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

#ifndef AIRBALL_MAP_OBJECTPREDICATES_HPP_
#define AIRBALL_MAP_OBJECTPREDICATES_HPP_

#include "Object.hpp"

#include "components/Description.hpp"

namespace airball
{
namespace map
{
namespace pred
{

bool any(const Object&)
{
    return true;
}

bool isPlayer(const Object& obj)
{
    return obj.getComponent<components::Description>().player;
}

bool isObstacle(const Object& obj)
{
    return obj.getComponent<components::Description>().obstacle;
}

bool isCreature(const Object& obj)
{
    return obj.getComponent<components::Description>().creature;
}

bool hasUuid(const Object& obj, unsigned uuid)
{
    return (obj.uuid() == uuid);
}

bool hasCoordinates(const Object& obj, const Coordinates& coord)
{
    return (obj.coordinates() == coord);
}

bool hasCoordinatesInRange(const Object& obj, const Coordinates& from, const Coordinates& to)
{
    const Coordinates& coord = obj.coordinates();
    return (coord.x >= from.x && coord.y < to.x && coord.y >= from.y && coord.y < to.y);
}

} // namespace pred
} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_OBJECTPREDICATES_HPP_
