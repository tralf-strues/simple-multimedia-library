//------------------------------------------------------------------------------
//! @author Nikita Mochalov (github.com/tralf-strues)
//! @file rectangle.h
//! @date 2021-10-29
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#ifndef RECTANGLE_H
#define RECTANGLE_H

template<typename T>
struct Rectangle
{
    Vec2<T> pos;
    
    T width;
    T height;
};

#endif // RECTANGLE_H