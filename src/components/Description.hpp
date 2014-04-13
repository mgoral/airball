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

#ifndef AIRBALL_COMPONENTS_DESCRIPTION_HPP_
#define AIRBALL_COMPONENTS_DESCRIPTION_HPP_

#include <memory>

#include "Component.hpp"

namespace airball
{
namespace components
{

/**
 * Basic component containing description of the objects. Each object should contain a Description
 * component.
 */
struct Description : public Component
{
    virtual Description* clone()
    {
        return new Description(*this);
    }

    // Please provide a sensible defaults for all properties.
    // When giving created ObjectProperties to objects, please fill all needed properties as the
    // defaults may change.

    std::string image = "";

    bool player = false;
    bool obstacle = false;
    bool creature = false;
};

} // namespace components
} // namespace airball

#endif // AIRBALL_COMPONENTS_DESCRIPTION_HPP_
