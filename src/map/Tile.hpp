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

#ifndef AIRBALL_MAP_TILE_HPP_
#define AIRBALL_MAP_TILE_HPP_

#include <string>

#include "Renderable.hpp"

namespace airball
{
namespace map
{

class Tile : public Renderable
{
public:
    explicit Tile(const std::string& imageName) :
        imageName_(imageName), obstacle_(false), stopsLight_(false), connector_(false, 0)
    {
    }

    explicit Tile(const std::string& imageName, bool obstacle) :
        imageName_(imageName), obstacle_(obstacle)
    {
    }

    std::string imageName() const
    {
        return imageName_;
    }

    void setObstacle(bool obstacle)
    {
        obstacle_ = obstacle;
    }

    bool isObstacle() const
    {
        return obstacle_;
    }

    void setStopLight(bool stopLight)
    {
        stopsLight_ = stopLight;
    }

    bool stopsLight() const
    {
        return stopsLight_;
    }

    void setConnector(unsigned levelUuid)
    {
        if (!connector_.first)
            connector_ = std::make_pair(true, levelUuid);
    }

    std::pair<bool, unsigned> connector() const
    {
        return connector_;
    }

private:
    std::string imageName_;
    bool obstacle_;
    bool stopsLight_;
    std::pair<bool, unsigned> connector_; // true/false, levelUuid
};

} // namespace map
} // namespace 

#endif // AIRBALL_MAP_TILE_HPP_
