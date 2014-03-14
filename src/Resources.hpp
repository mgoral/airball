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

#ifndef AIRBALL_RESOURCES_HPP_
#define AIRBALL_RESOURCES_HPP_

#include <stdexcept>
#include <mutex>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

namespace airball
{

class ResourcesError : public std::runtime_error
{
public:
    explicit ResourcesError(const std::string& what) : std::runtime_error(what)
    {
    }

    explicit ResourcesError(const char* what) : std::runtime_error(what)
    {
    }
};

class Resources
{
public:
    typedef std::unordered_map<std::string, SDL_Texture*> ResourceList;

    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

    static SDL_Texture* getImage(const std::string& imageName, SDL_Renderer* renderer);
    static void releaseImage(const std::string& imageName);
    static std::string getImagePath(const std::string& imageName);

protected:
    static void loadImage(const ResourceList::iterator& imageIt, SDL_Renderer* renderer);
    static std::string getResourcesRootDir();

private:
    static ResourceList resources_;
    static std::string pathSep_;

    // TODO: thread model is not yet created but it's possible that resources_ will be used from
    // many threads
    static std::mutex resourcesMutex_;
};

} // namespace airball

#endif // AIRBALL_RESOURCES_HPP_
