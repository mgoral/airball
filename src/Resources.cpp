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

#include <sstream>

#include <SDL2/SDL_image.h>

#include "Resources.hpp"

namespace airball
{

// Initialization of static member
std::mutex Resources::imagesMutex_;

Resources::ResourceList<SDL_Texture*> Resources::images_;
const boostfs::path Resources::airballDir_ = boostfs::current_path();

std::string Resources::getFilePath(const std::string& partialPath)
{
    return (getResourcesRootDir() + PATH_SEP + partialPath);
}

std::string Resources::joinPath(std::initializer_list<std::string> parts)
{
    std::stringstream path;
    std::initializer_list<std::string>::const_iterator it = parts.begin();

    if (it != parts.end())
    {
        path << *it;
        ++it;

        for (; it != parts.end(); ++it)
        {
            path << PATH_SEP;
            path << *it;
        }
    }

    return path.str();
}

SDL_Texture* Resources::getImage(const std::string& imageName, SDL_Renderer* renderer)
{
    std::lock_guard<std::mutex> lock(imagesMutex_);


    std::pair<ResourceList<SDL_Texture*>::iterator, bool> emplaceRet =
        images_.emplace(std::make_pair(imageName, nullptr));

    ResourceList<SDL_Texture*>::iterator imageIt = emplaceRet.first;
    if (emplaceRet.second)
    {
        loadImage(imageIt, renderer);
    }

    return imageIt->second;
}

void Resources::loadImage(const ResourceList<SDL_Texture*>::iterator& imageIt, SDL_Renderer* renderer)
{
    if (imageIt->second == nullptr)
    {
        std::string imagePath = getFilePath(joinPath({"img", imageIt->first}));
        SDL_Surface* surface = IMG_Load(imagePath.c_str());
        imageIt->second = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}

void Resources::releaseImage(const std::string& imageName)
{
    std::lock_guard<std::mutex> lock(imagesMutex_);

    ResourceList<SDL_Texture*>::iterator imageIt = images_.find(imageName);
    if (imageIt != images_.end() && imageIt->second != nullptr)
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
