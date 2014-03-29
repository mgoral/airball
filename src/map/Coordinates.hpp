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

#include <initializer_list>

namespace airball
{
namespace map
{

class Coordinates
{
public:
    Coordinates(int x, int y) : x(x), y(y)
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

    friend Coordinates operator+(const Coordinates& lhs, const Coordinates& rhs)
    {
        Coordinates temp = { lhs.x + rhs.x, lhs.y + rhs.y };
        return temp;
    }

    friend Coordinates& operator+=(Coordinates& lhs, const Coordinates& rhs)
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }

    friend Coordinates operator-(const Coordinates& lhs, const Coordinates& rhs)
    {
        Coordinates temp = { lhs.x - rhs.x, lhs.y - rhs.y };
        return temp;
    }

    friend Coordinates& operator-=(Coordinates& lhs, const Coordinates& rhs)
    {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;
        return lhs;
    }

    int x;
    int y;
};

} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_COORDINATES_HPP_
