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

#ifndef AIRBALL_MAP_OBJECT_HPP_
#define AIRBALL_MAP_OBJECT_HPP_

#include <string>
#include <memory>
#include <unordered_map>

#include "MapTypes.hpp"
#include "Renderable.hpp"
#include "Coordinates.hpp"

#include "components/Component.hpp"
#include "components/Description.hpp"

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
private:
    typedef std::unordered_map<unsigned, std::shared_ptr<components::Component>> Components;

public:
    Object(const Coordinates& coord, const components::Description& desc, unsigned uuid);

    Object(const Object& other);
    Object& operator=(Object other);
    friend void swap(Object& first, Object& second)
    {
        using std::swap;

        swap(first.coord_, second.coord_);
        swap(first.components_, second.components_);
        swap(first.uuid_, second.uuid_);
        swap(first.movingPath_, second.movingPath_);
    }

    SharedObjectPtr clone() const;

    static unsigned size();

    std::string imageName() const;

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

    unsigned uuid() const;

    template <typename T>
    void addComponent(const T& component)
    {
        // First check to avoid component copying on creation of unique_ptr
        if (components_.find(components::ComponentName<T>::classId()) == components_.end())
        {
            components_.insert(std::make_pair(
                components::ComponentName<T>::classId(),
                std::make_shared<T>(component)));
        }
    }

    template <typename T>
    bool hasComponent() const
    {
        return (components_.find(components::ComponentName<T>::classId()) != components_.end());
    }

    template <typename T>
    T& getComponent()
    {
        Components::iterator it = components_.find(components::ComponentName<T>::classId());
        if (it != components_.end())
            return *(std::static_pointer_cast<T>(it->second));
        throw std::invalid_argument("Component not found: " +
            std::to_string(components::ComponentName<T>::classId()));
    }

    template <typename T>
    const T& getComponent() const
    {
        Components::const_iterator it = components_.find(components::ComponentName<T>::classId());
        if (it != components_.end())
            return *(std::static_pointer_cast<const T>(it->second));
        throw std::invalid_argument("Component not found: " +
            std::to_string(components::ComponentName<T>::classId()));
    }

    friend bool operator<(const Object& lhs, const Object& rhs)
    {
        return (lhs.coordinates() < rhs.coordinates());
    }

private:
    void changeCoordinates(const Coordinates& coord);
    void setMovementAnimation(const Coordinates& to);

private:
    Coordinates coord_;
    Components components_;
    unsigned uuid_;

    Path movingPath_;
};

} // namespace map
} // namespace airball

#endif // AIRBALL_MAP_OBJECT_HPP_
