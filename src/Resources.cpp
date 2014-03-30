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

// Initialization of static member
std::mutex Resources::resourcesMutex_;

Resources::ResourceList Resources::resources_;
const boostfs::path Resources::airballDir_ = boostfs::current_path();

SDL_Texture* Resources::getImage(const std::string& imageName, SDL_Renderer* renderer)
{
    std::lock_guard<std::mutex> lock(resourcesMutex_);


    std::pair<ResourceList::iterator, bool> emplaceRet =
        resources_.emplace(std::make_pair(imageName, nullptr));

    ResourceList::iterator imageIt = emplaceRet.first;
    if (emplaceRet.second)
    {
        loadImage(imageIt, renderer);
    }

    return imageIt->second;
}

std::string Resources::getImagePath(const std::string& imageName)
{
    return (getResourcesRootDir() + PATH_SEP + "img" + PATH_SEP + imageName);
}

void Resources::loadImage(const ResourceList::iterator& imageIt, SDL_Renderer* renderer)
{
    if (imageIt->second == nullptr)
    {
        std::string imagePath = getImagePath(imageIt->first);
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
    return (airballDir_.string() + PATH_SEP + "resources");
}

} // namespace airball
