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

#include "EventHandler.hpp"

namespace airball
{

void EventHandler::registerAction(const KeyInfo& keyInfo, const std::shared_ptr<IAction>& action)
{
    actionMap_[keyInfo] = action;
}

void EventHandler::deregisterAction(const KeyInfo& keyInfo)
{
    ActionMap::iterator actionIt = actionMap_.find(keyInfo);
    if (actionIt != actionMap_.end())
        actionMap_.erase(actionIt);
}

void EventHandler::runAction(const KeyInfo& keyInfo) const
{
    ActionMap::const_iterator actionIt = actionMap_.find(keyInfo);
    if (actionIt != actionMap_.end())
        actionIt->second->run();

}

} // namespace airball
