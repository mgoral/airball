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

/*
 * Object
 */

Object::Object(const Coordinates& coord, const ObjectProperties& properties, unsigned uuid) :
    coord_(coord), properties_(properties), uuid_(uuid), animation_(8)
{
    // Init animation.
    setMovementAnimation(coord_);
}

SharedObjectPtr Object::clone() const
{
    return std::make_shared<Object>(*this);
}

unsigned Object::size()
{
    return 32;
}

std::string Object::imageName() const
{
    return properties_.image;
}

Animation& Object::getAnimation() const
{
    return animation_;
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
    setMovementAnimation(coord);
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

void Object::setMovementAnimation(const Coordinates& to)
{
    SDL_Rect source = {
        static_cast<int>(map::Object::size()) * coord_.x,
        static_cast<int>(map::Object::size()) * coord_.y,
        static_cast<int>(map::Object::size()),
        static_cast<int>(map::Object::size())
    };

    SDL_Rect destination = {
        static_cast<int>(map::Object::size()) * to.x,
        static_cast<int>(map::Object::size()) * to.y,
        static_cast<int>(map::Object::size()),
        static_cast<int>(map::Object::size())
    };

    animation_.reset();
    animation_.setMovementSource(source);
    animation_.setMovementDestination(destination);
}

} // namespace map
} // namespace airball
