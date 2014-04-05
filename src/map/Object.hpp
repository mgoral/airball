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

#ifndef AIRBALL_MAP_OBJECT_HPP_
#define AIRBALL_MAP_OBJECT_HPP_

#include <memory>

#include "MapTypes.hpp"
#include "Renderable.hpp"
#include "Coordinates.hpp"
#include "ObjectProperties.hpp"
#include "Animation.hpp"

namespace airball
{
namespace map
{

class Object;

typedef std::shared_ptr<airball::map::Object> SharedObjectPtr;
typedef std::shared_ptr<const airball::map::Object> SharedCObjectPtr;
typedef std::weak_ptr<airball::map::Object> WeakObjectPtr;
typedef std::weak_ptr<const airball::map::Object> WeakCObjectPtr;


class Object : public airball::Renderable
{
public:
    Object(const Coordinates& coord, const ObjectProperties& properties, unsigned uuid);

    SharedObjectPtr clone() const;

    static unsigned size();

    std::string imageName() const;

    Animation& getAnimation() const;

    Coordinates coordinates() const;
    void teleportTo(const Coordinates& coord);
    bool isNeighbour(const Object& other) const;

    /**
     * Set and move on predefined path.
     */
    void clearPath();
    void setMovingPath(const Path& movingPath);
    void moveBySingleStep();
    const Coordinates& nextStep() const; // UNDEFINED BEHAVIOUR FOR EMPTY PATHS!
    const Path& movingPath() const;

    ObjectProperties& properties();
    const ObjectProperties& properties() const;
    unsigned uuid() const;

    friend bool operator<(const Object& lhs, const Object& rhs)
    {
        return (lhs.coordinates() < rhs.coordinates());
    }

private:
    void changeCoordinates(const Coordinates& coord);
    void setMovementAnimation(const Coordinates& to);

private:
    Coordinates coord_;
    ObjectProperties properties_;
    unsigned uuid_;

    Path movingPath_;

    // Animation affects only visual appearance of Object and is not very important from any point
    // of view, so we'll make it mutable to easily pass to Screen::addAnimatedRenderable. 
    // It's a little dirty hack though, no matter how we'll try to excuse it.
    mutable Animation animation_;
};

} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_OBJECT_HPP_
