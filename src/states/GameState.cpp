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

#include "detail/Utils.hpp"

#include "GameState.hpp"

#include "map/ObjectProperties.hpp"

namespace airball
{
namespace states
{

map::ObjectProperties playerPropertiesFactory()
{
    map::ObjectProperties prop;
    prop.image = "player.png";

    return prop;
}

GameState::GameState() :
    currentLevel_(200, 100)  // TODO: different (random?) level size
    //player_(map::Coordinates(5,5), playerPropertiesFactory())
{
    // TODO: objects factory (with uuid assigner)
    player_ = std::make_shared<map::Object>(map::Coordinates(50, 50), playerPropertiesFactory(), 0);
    currentLevel_.addObject(player_);
}

void GameState::onEnter()
{
}

void GameState::onExit()
{
}

void GameState::onOverride()
{
}

void GameState::onResume()
{
}


void GameState::handleEvent(SDL_Event& event)
{
    UNUSED_PARAM(event);
}

void GameState::update(StateStack& stack)
{
    UNUSED_PARAM(stack);
}

void GameState::draw(airball::Screen& screen)
{
    screen.clear();

    map::Coordinates wh = currentLevel_.dimensions();
    for (unsigned x = 0; x < wh.x; ++x)
    {
        for (unsigned y = 0; y < wh.y; ++y)
        {
            map::Coordinates coord(x, y);
            const map::Tile& tile = currentLevel_.tile(coord);
            if (tile.imageName() != "empty")
            {
                // FIXME: remove that shitty Object::size()! Better hardcode it in screen or
                // somewhere
                SDL_Rect destination = {
                    static_cast<int>(x),
                    static_cast<int>(y),
                    static_cast<int>(map::Object::size()),
                    static_cast<int>(map::Object::size())
                };
                screen.addRenderable(tile, &destination);
            }
        }
    }

    for (const map::SharedCObjectPtr& object : currentLevel_.objects())
    {
        map::Coordinates coord = object->coordinates();
        SDL_Rect destination = {
            static_cast<int>(coord.x),
            static_cast<int>(coord.y),
            static_cast<int>(map::Object::size()),
            static_cast<int>(map::Object::size())
        };
        screen.addRenderable(*object, &destination);
    }

    screen.update();
}


} // namespace states
} // namespace airball
