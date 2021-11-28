/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file rectangle.cpp
 * @date 2021-11-27
 * 
 * @copyright Copyright (c) 2021
 */

#include "math/rectangle.h"

namespace Sml
{
    SDL_Rect toNativeRectangle(const Rectangle<int32_t>& rectangle)
    {
        SDL_Rect nativeRectangle;

        nativeRectangle.x = rectangle.pos.x;
        nativeRectangle.y = rectangle.pos.y;
        nativeRectangle.w = rectangle.width;
        nativeRectangle.h = rectangle.height;

        return nativeRectangle;
    }
}