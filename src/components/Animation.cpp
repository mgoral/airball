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

#include <algorithm>

#include "Animation.hpp"

namespace airball
{
namespace components
{

Animation::Animation(const SDL_Rect& source, const SDL_Rect& destination,
    unsigned startFrames, bool loop) :
        source_(source), destination_(destination), frames_(startFrames), loop_(loop),
        currentFrame_(0)
{
}

Animation::Animation(const SDL_Rect& source, const SDL_Rect& destination, unsigned startFrames) :
    Animation(source, destination, startFrames, false)
{
}

Animation::Animation(unsigned startFrames) : Animation({0, 0, 0, 0}, {0, 0, 0, 0}, startFrames)
{
}

Animation::Animation() : Animation({0, 0, 0, 0}, {0, 0, 0, 0}, 0)
{
}

bool Animation::done() const
{
    return (!loop_ && (frames_.empty() || currentFrame_ + 1 == frames_.size()));
}

void Animation::setMovementSource(const SDL_Rect& source)
{
    source_ = source;
}

void Animation::setMovementDestination(const SDL_Rect& destination)
{
    destination_ = destination;
}

const SDL_Rect* Animation::movementSource() const
{
    return &source_;
}

const SDL_Rect* Animation::movementDestination() const
{
    return &destination_;
}

const SDL_Rect* Animation::frame() const
{
    if (!frames_.empty())
    {
        const SDL_RectPtr& frame = frames_[currentFrame_];
        if (frame)
        {
            return &*frames_[currentFrame_];
        }
    }
    return nullptr;
}

SDL_Rect Animation::position() const
{
    if (done())
    {
        return destination_;
    }

    int framePathX = destination_.x - source_.x;
    int framePathY = destination_.y - source_.y;

    SDL_Rect ret;
    ret.x = source_.x + framePathX * (float(currentFrame_) / float(frames_.size() + 1));
    ret.y = source_.y + framePathY * (float(currentFrame_) / float(frames_.size() + 1));
    ret.w = source_.w;
    ret.h = source_.h;

    return ret;
}

void Animation::reset()
{
    currentFrame_ = 0;
}

void Animation::addFrame(const std::shared_ptr<SDL_Rect>& frame)
{
    frames_.push_back(frame);
}

void Animation::addEmptyFrames(unsigned no)
{
    for (unsigned i = 0; i < no; ++i)
    {
        frames_.push_back(SDL_RectPtr());
    }
}

void Animation::setLoop(bool enable)
{
    loop_ = enable;
}

void Animation::clear()
{
    currentFrame_ = 0;
    frames_.clear();
}

Animation& Animation::operator++()
{
    if (!done())
        currentFrame_ = (currentFrame_ + 1) % frames_.size();

    return *this;
}

Animation Animation::operator++(int)
{
    Animation ret(*this);
    operator++();
    return ret;
}


} // namespace components
} // namespace airball
