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
 */

#include <algorithm>

#include "Object.hpp"

#include "components/Animation.hpp"

#include "detail/Utils.hpp"

namespace airball
{
namespace map
{

/*
 * Object
 */

Object::Object(
    const Coordinates& coord, const components::Description& description, unsigned uuid) :
        coord_(coord), uuid_(uuid)
{
    addComponent(description);
}

Object::Object(const Object& other) :
    coord_(other.coord_), uuid_(other.uuid_), movingPath_(other.movingPath_)
{
    for (const Components::value_type& val : other.components_)
    {
        components_[val.first].reset(val.second->clone());
    }
}

Object& Object::operator=(Object other)
{
    swap(*this, other);
    return *this;
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
    components::Description descr = getComponent<components::Description>();
    return descr.image;
}

Coordinates Object::coordinates() const
{
    return coord_;
}

void Object::teleportTo(const Coordinates& coord)
{
    try
    {
        getComponent<components::Animation>().clear();
    }
    catch(const std::invalid_argument&) // No Animation
    {
    }

    movingPath_.clear();
    coord_ = coord;
}

bool Object::isNeighbour(const Object& other) const
{
    unsigned distX = std::max(coord_.x, other.coord_.x) - std::min(coord_.x, other.coord_.x);
    unsigned distY = std::max(coord_.y, other.coord_.y) - std::min(coord_.y, other.coord_.y);
    return (distX == 1 && distY == 1);
}

void Object::clearPath()
{
    movingPath_.clear();
}

void Object::setMovingPath(const Path& movingPath)
{
    movingPath_ = movingPath;

    // Postprocess Path
    while (!movingPath_.empty() && movingPath_.back() == coordinates())
        movingPath_.pop_back();
}

void Object::moveBySingleStep()
{
    if (!movingPath_.empty())
    {
        changeCoordinates(movingPath_.back());
        movingPath_.pop_back();
    }
}

const Coordinates& Object::nextStep() const // UNDEFINED BEHAVIOUR FOR EMPTY PATHS!
{
    return movingPath_.back();
}

const Path& Object::movingPath() const
{
    return movingPath_;
}

unsigned Object::uuid() const
{
    return uuid_;
}

void Object::changeCoordinates(const Coordinates& coord)
{
    setMovementAnimation(coord);
    coord_ = coord;
}

void Object::setMovementAnimation(const Coordinates& to)
{
    try
    {
        components::Animation& animation = getComponent<components::Animation>();

        SDL_Rect source = detail::coord2Rect(coord_, map::Object::size());
        SDL_Rect destination = detail::coord2Rect(to, map::Object::size());

        animation.reset();
        animation.setMovementSource(source);
        animation.setMovementDestination(destination);
    }
    catch (const std::invalid_argument&) // no Animation component
    {
    }
}

} // namespace map
} // namespace airball
