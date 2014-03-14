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



#ifndef AIRBALL_MAP_COORDINATES_HPP_
#define AIRBALL_MAP_COORDINATES_HPP_

namespace airball
{
namespace map
{

struct Coordinates
{
    Coordinates(unsigned x, unsigned y) : x(x), y(y)
    {
    }

    friend bool operator==(const Coordinates& lhs, const Coordinates& rhs)
    {
        return (lhs.x == rhs.x && lhs.y == rhs.y);
    }

    friend bool operator!=(const Coordinates& lhs, const Coordinates& rhs)
    {
        return !(lhs == rhs);
    }

    friend bool operator<(const Coordinates& lhs, const Coordinates& rhs)
    {
        return ((lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y)));
    }

    unsigned x;
    unsigned y;
};

} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_COORDINATES_HPP_
