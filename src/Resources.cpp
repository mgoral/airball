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

#include <SDL2/SDL_image.h>

#include "Resources.hpp"

namespace airball
{

#ifdef WIN32
std::string Resources::pathSep_ = "\\";
#else
std::string Resources::pathSep_ = "/";
#endif

Resources::ResourceList Resources::resources_ =
{
    {"player.png", nullptr},
    {"wall.png", nullptr},
};

std::mutex Resources::resourcesMutex_;

SDL_Texture* Resources::getImage(const std::string& imageName, SDL_Renderer* renderer)
{
    std::lock_guard<std::mutex> lock(resourcesMutex_);

    ResourceList::iterator imageIt = resources_.find(imageName);
    if (imageIt != resources_.end())
    {
        loadImage(imageIt, renderer);
        return imageIt->second;
    }

    return nullptr;
}

std::string Resources::getImagePath(const std::string& imageName)
{
    return (getResourcesRootDir() + pathSep_ + imageName);
}

void Resources::loadImage(const ResourceList::iterator& imageIt, SDL_Renderer* renderer)
{
    if (imageIt->second == nullptr)
    {
        std::string imagePath = getResourcesRootDir() + pathSep_ + imageIt->first;
        SDL_Surface* surface = IMG_Load(imagePath.c_str());
        imageIt->second = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}

void Resources::releaseImage(const std::string& imageName)
{
    std::lock_guard<std::mutex> lock(resourcesMutex_);

    ResourceList::iterator imageIt = resources_.find(imageName);
    if (imageIt != resources_.end() && imageIt->second != nullptr)
    {
        SDL_DestroyTexture(imageIt->second);
        imageIt->second = nullptr;
    }
}

std::string Resources::getResourcesRootDir()
{
// TODO: airball resources will not be stored like that.
#ifdef UNIX
    std::string homedir = std::getenv("HOME");
    std::string configDir = homedir + pathSep_ + ".config";
#else
    std::string configDir = "";
#endif

    return (configDir + pathSep_ + "airball");
}

} // namespace airball
