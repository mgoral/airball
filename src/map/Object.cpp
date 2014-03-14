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

#include <algorithm>

#include "Object.hpp"

namespace airball
{
namespace map
{

unsigned Object::size_ = 32;

/*
 * Object
 */

Object::Object(const Coordinates& coord, const ObjectProperties& properties, unsigned uuid) :
    coord_(coord), properties_(properties), uuid_(uuid)
{
}

SharedObjectPtr Object::clone() const
{
    return std::make_shared<Object>(*this);
}

unsigned Object::size()
{
    return size_;
}

std::string Object::imageName() const
{
    return properties_.image;
}

Coordinates Object::coordinates() const
{
    return coord_;
}

bool Object::isNeighbour(const Object& other) const
{
    unsigned distX = std::max(coord_.x, other.coord_.x) - std::min(coord_.x, other.coord_.x);
    unsigned distY = std::max(coord_.y, other.coord_.y) - std::min(coord_.y, other.coord_.y);
    return (distX == 1 && distY == 1);
}

void Object::changeCoordinates(const Coordinates& coord)
{
    coord_ = coord;
}

ObjectProperties& Object::properties()
{
    return properties_;
}

const ObjectProperties& Object::properties() const
{
    return properties_;
}

unsigned Object::uuid() const
{
    return uuid_;
}

} // namespace map
} // namespace airball
