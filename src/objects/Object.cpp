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

#include "Object.hpp"

namespace airball
{
namespace objects
{

Object::Object(const Coordinates& coord, unsigned radius) : coord_(coord), radius_(radius)
{
}

bool Object::collides(const Object& other) const
{
    unsigned radiusSum = radius_ + other.radius_;
    int distanceX = coord_.x - other.coord_.x;
    int distanceY = coord_.y - other.coord_.y;

    return ((radiusSum * radiusSum) >= static_cast<unsigned>(
        distanceX * distanceX + distanceY * distanceY));
}


} // namespace objects
} // namespace airball
