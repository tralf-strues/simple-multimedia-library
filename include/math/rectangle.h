/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file rectangle.h
 * @date 2021-10-29
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

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
}

#endif // RECTANGLE_H