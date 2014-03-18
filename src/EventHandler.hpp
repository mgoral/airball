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

#ifndef AIRBALL_EVENTHANDLER_HPP_
#define AIRBALL_EVENTHANDLER_HPP_

#include <string>
#include <map>
#include <memory>

#include <SDL2/SDL.h>

#include "IAction.hpp"

namespace airball
{

struct KeyInfo
{
    uint16_t mod;
    SDL_Keycode keycode;

    bool friend operator==(const KeyInfo& lhs, const KeyInfo& rhs)
    {
        return (lhs.mod == rhs.mod && lhs.keycode == rhs.keycode);
    }

    bool friend operator!=(const KeyInfo& lhs, const KeyInfo& rhs)
    {
        return !(lhs == rhs);
    }

    bool friend operator<(const KeyInfo& lhs, const KeyInfo& rhs)
    {
        return ((lhs.mod < rhs.mod) || (lhs.mod == rhs.mod && lhs.keycode < rhs.keycode));
    }
};

class EventHandler
{
public:
    EventHandler() = default;
    EventHandler(const EventHandler&) = delete;
    EventHandler& operator=(const EventHandler&) = delete;

    typedef std::map<KeyInfo, std::shared_ptr<IAction> > ActionMap;

    void registerAction(const KeyInfo& keyInfo, const std::shared_ptr<IAction>& action);
    void deregisterAction(const KeyInfo& keyInfo);
    void runAction(const KeyInfo& keyInfo) const;

private:
    ActionMap actionMap_;
};

} // namespace airball

#endif // AIRBALL_EVENTHANDLER_HPP_
