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
#include <cstdlib>
#include <vector>

#ifndef NDEBUG
#include <ostream>
#endif

namespace airball
{
namespace map
{


class Coordinates
{
public:
    Coordinates(int x, int y) noexcept : x(x), y(y)
    {
    }

    template <typename T>
    bool inBoundaries(const std::vector<std::vector<T>>& toCheck) const
    {
        return (x >= 0 && y >= 0 && x < toCheck.size() && y < toCheck[x].size());
    }

    bool isNeighbour(const Coordinates& other) const
    {
        return (std::abs(x - other.x) <= 1 && std::abs(y - other.y) <= 1);
    }

    int x;
    int y;

#ifndef NDEBUG
    friend std::ostream& operator<<(std::ostream& stream, const Coordinates& coord)
    {
        return stream << "(" << coord.x << ", " << coord.y << ")";
    }
#endif
};

bool operator==(const Coordinates& lhs, const Coordinates& rhs);
bool operator!=(const Coordinates& lhs, const Coordinates& rhs);
bool operator<(const Coordinates& lhs, const Coordinates& rhs);

Coordinates operator+(const Coordinates& lhs, const Coordinates& rhs);
Coordinates& operator+=(Coordinates& lhs, const Coordinates& rhs);
Coordinates operator-(const Coordinates& lhs, const Coordinates& rhs);
Coordinates& operator-=(Coordinates& lhs, const Coordinates& rhs);

std::size_t hash_value(const Coordinates& coord);

// Some type definitions
typedef std::vector<Coordinates> CoordinatesVector;

} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_COORDINATES_HPP_
