/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file rectangle.h
 * @date 2021-10-29
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

namespace Sml
{
    template<typename T>
    struct Rectangle
    {
        Vec2<T> pos;
        
        T width;
        T height;
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
}
