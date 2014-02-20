/**
 * Copyright (C) Michal Goral, 2014
 *
 * Airball is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Airball is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Airball; if not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef AIRBALL_STATES_ISTATE_HPP_
#define AIRBALL_STATES_ISTATE_HPP_

namespace airball
{
namespace states
{

class StateStack;

class IState
{
public:
    virtual ~IState()
    {
    }

    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void onOverride() = 0;
    virtual void onResume() = 0;

    virtual void update(StateStack& stack) = 0;
};

} // namespace states
} // namespace airball

#endif // AIRBALL_STATES_ISTATE_HPP_
