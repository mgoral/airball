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

#ifndef AIRBALL_STATES_GAMESTATE_HPP_
#define AIRBALL_STATES_GAMESTATE_HPP_

#include <vector>

#include "EventHandler.hpp"
#include "Logger.hpp"

#include "IState.hpp"

#include "map/World.hpp"

namespace airball
{
namespace states
{

class GameState : public IState
{
public:
    GameState();

    void onEnter();
    void onExit();
    void onOverride();
    void onResume();

    void handleEvent(SDL_Event& event);
    void update(StateStack& stack);
    void draw(airball::Screen& screen);

private:
    map::World world_;
    EventHandler eventHandler_;
    Logger logger_;
};

} // namespace states
} // namespace airball

#endif // AIRBALL_STATES_GAMESTATE_HPP_
