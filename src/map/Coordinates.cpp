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

#include <boost/functional/hash.hpp>

#include "Coordinates.hpp"

namespace airball
{
namespace map
{

bool operator==(const Coordinates& lhs, const Coordinates& rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool operator!=(const Coordinates& lhs, const Coordinates& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Coordinates& lhs, const Coordinates& rhs)
{
    return ((lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y)));
}

Coordinates operator+(const Coordinates& lhs, const Coordinates& rhs)
{
    Coordinates temp = { lhs.x + rhs.x, lhs.y + rhs.y };
    return temp;
}

Coordinates& operator+=(Coordinates& lhs, const Coordinates& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

Coordinates operator-(const Coordinates& lhs, const Coordinates& rhs)
{
    Coordinates temp = { lhs.x - rhs.x, lhs.y - rhs.y };
    return temp;
}

Coordinates& operator-=(Coordinates& lhs, const Coordinates& rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}

std::size_t hash_value(const Coordinates& coord)
{
    boost::hash<std::pair<int, int>> hasher;
    return hasher(std::make_pair(coord.x, coord.y));
}

} // namespace map
} // namespace airball
