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
#include "detail/Translate.hpp"

#include "GameState.hpp"
#include "EventHandler.hpp"

#include "map/ObjectProperties.hpp"

#include <iostream>

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
    currentLevel_(200, 100),  // TODO: different (random?) level size
    logger_(LogCategoryApplication)
{
    logger_.info(_("Initializing Airball"));

    // TODO: objects factory (with uuid assigner)
    map::Coordinates playerCoordinates(0, 0);
    map::SharedCObjectPtr futurePlayer =
        std::make_shared<map::Object>(playerCoordinates, playerPropertiesFactory(), 0);
    if (currentLevel_.addObject(futurePlayer))
    {
        std::vector<map::SharedCObjectPtr> objects = currentLevel_.objectsAt(playerCoordinates);
        player_ = objects[0];

        eventHandler_.registerAction(
            { KMOD_NONE, SDLK_h },
            std::make_shared<MoveAction>(currentLevel_, player_, map::Coordinates(-1, 0)));
        eventHandler_.registerAction(
            { KMOD_NONE, SDLK_j },
            std::make_shared<MoveAction>(currentLevel_, player_, map::Coordinates(0, 1)));
        eventHandler_.registerAction(
            { KMOD_NONE, SDLK_k },
            std::make_shared<MoveAction>(currentLevel_, player_, map::Coordinates(0, -1)));
        eventHandler_.registerAction(
            { KMOD_NONE, SDLK_l },
            std::make_shared<MoveAction>(currentLevel_, player_, map::Coordinates(1, 0)));
        eventHandler_.registerAction(
            { KMOD_NONE, SDLK_y },
            std::make_shared<MoveAction>(currentLevel_, player_, map::Coordinates(-1, -1)));
        eventHandler_.registerAction(
            { KMOD_NONE, SDLK_u },
            std::make_shared<MoveAction>(currentLevel_, player_, map::Coordinates(1, -1)));
        eventHandler_.registerAction(
            { KMOD_NONE, SDLK_b },
            std::make_shared<MoveAction>(currentLevel_, player_, map::Coordinates(-1, 1)));
        eventHandler_.registerAction(
            { KMOD_NONE, SDLK_n },
            std::make_shared<MoveAction>(currentLevel_, player_, map::Coordinates(1, 1)));
    }
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
    switch (event.type)
    {
        case SDL_KEYDOWN:
            SDL_Keysym pressedKey = event.key.keysym;
            KeyInfo keyInfo = { pressedKey.mod, pressedKey.sym };
            eventHandler_.runAction(keyInfo);
            break;
    }
}

void GameState::update(StateStack& stack)
{
    UNUSED_PARAM(stack);
}

void GameState::draw(airball::Screen& screen)
{
    screen.clear();

    map::Coordinates wh = currentLevel_.dimensions();
    for (int x = 0; x < wh.x; ++x)
    {
        for (int y = 0; y < wh.y; ++y)
        {
            map::Coordinates coord(x, y);
            const map::Tile& tile = currentLevel_.tile(coord);
            if (tile.imageName() != "empty")
            {
                // FIXME: remove that shitty Object::size()! Better hardcode it in screen or
                // somewhere
                SDL_Rect destination = {
                    static_cast<int>(map::Object::size()) * x,
                    static_cast<int>(map::Object::size()) * y,
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
            static_cast<int>(map::Object::size()) * coord.x,
            static_cast<int>(map::Object::size()) * coord.y,
            static_cast<int>(map::Object::size()),
            static_cast<int>(map::Object::size())
        };
        screen.addRenderable(*object, &destination);
    }

    screen.update();
}


} // namespace states
} // namespace airball
