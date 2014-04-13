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

#ifndef AIRBALL_COMPONENTS_COMPONENT_HPP
#define AIRBALL_COMPONENTS_COMPONENT_HPP

#include <memory>

namespace airball
{
namespace components
{

/**
 * Abstract base class for all components.
 */
class Component
{
public:
    virtual ~Component()
    {
    }

    // virtual copy constructor
    virtual Component* clone() = 0;
};

template <typename T>
class ComponentName
{
public:
    // This function MUST BE specialized for each component! If it is not specialized, it will
    // cause a compilation error!
    static unsigned classId()
    {
        static_assert(sizeof(ComponentName) != sizeof(ComponentName),
            "Type not specialized! Cannot use Generic getClassId()!");
        return 0;
    }
};

// ComponentName specializations start
// These are only forward declarations. Concrete implementations are in ComponentNames.cpp

class Animation;
class Description;

template<> unsigned ComponentName<Animation>::classId();
template<> unsigned ComponentName<Description>::classId();

// ComponentName specializations end 

} // namespace components
} // namespace airball

#endif // AIRBALL_COMPONENTS_COMPONENT_HPP
