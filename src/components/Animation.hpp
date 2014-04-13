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

#ifndef AIRBALL_COMPONENTS_ANIMATION_HPP_
#define AIRBALL_COMPONENTS_ANIMATION_HPP_

#include <memory>
#include <vector>

#include <SDL2/SDL.h>

#include "Component.hpp"

namespace airball
{
namespace components
{

typedef std::shared_ptr<SDL_Rect> SDL_RectPtr;

/**
 * Animation wrapper. Animations can move around the screen (change position) and change their
 * appearence (image). They can also be looped or not. It's usually a stupid idea to loop animation
 * that changes its position as well.
 *
 * Animation doesn't contain image that should be animated. It's a kind of 'filter' applied to the
 * external image.
 *
 * Each animation is built from several frames that describe which part of image should be
 * displayed. Frames can be empty - in that case the whole image will be rendered. It is useful
 * e.g. for moving animations, where the whole image is moved around the screen.
 */
class Animation : public Component
{
public:
    Animation(const SDL_Rect& source, const SDL_Rect& destination, unsigned startFrames, bool loop);
    Animation(const SDL_Rect& source, const SDL_Rect& destination, unsigned startFrames);
    explicit Animation(unsigned startFrames);
    Animation();

    Animation* clone()
    {
        return new Animation(*this);
    }

    /**
     * Is animation finished. If it's not looped animation, it's considered finished on the last
     * frame.
     */
    bool done() const;

    /**
     * Set and get positions of animation. If source and destination positions are not equal, it
     * means that image should move aroud the screen.
     */
    void setMovementSource(const SDL_Rect& source);
    void setMovementDestination(const SDL_Rect& destination);
    const SDL_Rect* movementSource() const;
    const SDL_Rect* movementDestination() const;

    /**
     * Get SDL_Rect describing a part of image that should be rendered during current animation
     * frame.
     */
    const SDL_Rect* frame() const;

    /**
     * Get screen position where image should be rendered.
     */
    SDL_Rect position() const;

    /**
     * Adds new frames (empty or not).
     */
    void addFrame(const std::shared_ptr<SDL_Rect>& frame);
    void addEmptyFrames(unsigned no);

    /**
     * Change whether animation should be looped or not
     */
    void setLoop(bool enable);

    /**
     * Resets animation to the first frame.
     */
    void reset();

    /**
     * Remove all animatino frames.
     */
    void clear();

    /**
     * Changes current animation frame to the next one.
     */
    Animation& operator++();   // preincrementation (++animation)
    Animation operator++(int); // postincrementation (animation++)

private:
    SDL_Rect source_;
    SDL_Rect destination_;
    std::vector<SDL_RectPtr> frames_;
    unsigned fps_;
    bool loop_;
    unsigned currentFrame_;
};

} // namespace components
} // namespace airball

#endif // AIRBALL_COMPONENTS_ANIMATION_HPP_
