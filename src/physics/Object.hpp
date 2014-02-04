/**
 * Copyright (C) Michal Goral, 2014
 *
 * Airball is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Airball is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Airball; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef AIRBALL_PHYSICS_OBJECT_HPP_
#define AIRBALL_PHYSICS_OBJECT_HPP_

#include "Coordinates.hpp"

namespace physics
{

/**
 * A circular object that has coordinates of its center and a radius.
 */
class Object
{
public:
    Object(const Coordinates& coord, unsigned radius);

private:
    Coordinates coord_;
    unsigned radius_;
};

} // namespace physics

#endif // AIRBALL_PHYSICS_OBJECT_HPP_
