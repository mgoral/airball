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

#ifndef AIRBALL_STATES_STATESTACK_HPP_
#define AIRBALL_STATES_STATESTACK_HPP_

#include <memory>
#include <vector>

#include "IState.hpp"

namespace airball
{
namespace states
{

class StateStack
{
public:
    StateStack();
    ~StateStack();

    /**
     * Checks if state on top of the stack has finished and pops it in that case.
     * This method should be called periodically (e.g. each frame)
     */

    void update();
    void push(std::unique_ptr<IState> state);
    void pop();

private:
    void processEvents();

    void pushEvent(std::unique_ptr<IState> state);
    void popEvent();

private:
    std::vector<std::unique_ptr<IState>> stateStack_;
    std::vector<std::function<void()>> events_;
    bool updateStarted_;
};

} // namespace states
} // namespace airball

#endif // AIRBALL_STATES_STATESTACK_HPP_
