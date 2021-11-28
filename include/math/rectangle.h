/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file rectangle.h
 * @date 2021-10-29
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <SDL.h>
#include "vec2.h"

namespace Sml
{
    template<typename T>
    struct Rectangle
    {
        Vec2<T> pos;
        
        T width;
        T height;

        Rectangle() = default;

        Rectangle(const Vec2<T>& pos, const T& width, const T& height)
            : pos(pos), width(width), height(height) {}

        Rectangle(const T& posX, const T& posY, const T& width, const T& height)
            : Rectangle(Vec2<T>{posX, posY}, width, height) {}
    };

    template<typename T>
    Rectangle<T> centerRegion(const Rectangle<T>& region, const Rectangle<T>& innerRegion)
    {
        T offsetX = region.pos.x + (region.width  - innerRegion.width)  / 2;
        T offsetY = region.pos.y + (region.height - innerRegion.height) / 2;

        return Rectangle<T>{Vec2<T>{offsetX, offsetY}, innerRegion.width, innerRegion.height};
    }

    template<typename T>
    bool isPointInsideRectangle(const Vec2<T>& point, const Rectangle<T>& rectangle)
    {
        return point.x >= rectangle.pos.x && point.x <= (rectangle.pos.x + rectangle.width) &&
               point.y >= rectangle.pos.y && point.y <= (rectangle.pos.y + rectangle.height);
    }

    SDL_Rect toNativeRectangle(const Rectangle<int32_t>& rectangle);
}
