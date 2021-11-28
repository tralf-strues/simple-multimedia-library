/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file color.h
 * @date 2021-09-05
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <stdint.h>
#include <SDL.h>
#include "../math/vec4.h"

namespace Sml
{
    typedef uint32_t Color;

    static const Color COLOR_TRANSPARENT = 0x00'00'00'00;
    static const Color COLOR_WHITE       = 0xFF'FF'FF'FF;
    static const Color COLOR_BLACK       = 0x00'00'00'FF;
    static const Color COLOR_RED         = 0xFF'00'00'FF;
    static const Color COLOR_GREEN       = 0x00'FF'00'FF;
    static const Color COLOR_BLUE        = 0x00'00'FF'FF;
    static const Color COLOR_YELLOW      = 0xFF'FF'00'FF;

    static inline uint8_t getByte(uint32_t number, uint8_t byteNumber)
    {
        return (number & (0xFFu << (8u * byteNumber))) >> (8u * byteNumber);
    }

    /**
     * @brief Creates Color from separate color chanels - rgba.
     * 
     * @param r Red value.
     * @param g Green value.
     * @param b Blue value.
     * @param a Alpha value.
     * 
     * @return Created rgba color. 
     */
    static inline Color rgbaColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        return ((uint32_t) r << 24u) + ((uint32_t) g << 16u) + ((uint32_t) b << 8u ) + (uint32_t) a;
    }

    /**
     * @param color 
     * @return Color's red chanel. 
     */
    static inline uint8_t colorGetR(Color color)
    {
        return getByte(color, 3u);
    }

    /**
     * @param color 
     * @return Color's green chanel. 
     */
    static inline uint8_t colorGetG(Color color)
    {
        return getByte(color, 2u);
    }

    /**
     * @param color 
     * @return Color's blue chanel. 
     */
    static inline uint8_t colorGetB(Color color)
    {
        return getByte(color, 1u);
    }

    /**
     * @param color 
     * @return Color's alpha chanel. 
     */
    static inline uint8_t colorGetA(Color color)
    {
        return getByte(color, 0u);
    }

    /**
     * @brief Convert rgba color to normalized floating-point vector.
     * 
     * @param color
     * 
     * @return Normalized color.
     */
    static inline Vec4<float> colorToNormalized(Color color)
    {
        Vec4<float> floatColor;

        floatColor.x = static_cast<float>(colorGetR(color)) / 255.f;
        floatColor.y = static_cast<float>(colorGetG(color)) / 255.f;
        floatColor.z = static_cast<float>(colorGetB(color)) / 255.f;
        floatColor.w = static_cast<float>(colorGetA(color)) / 255.f;

        return floatColor;
    }

    /**
     * @brief Convert normalized floating-point vector to rgba color.
     * 
     * @param normalizedColor
     * 
     * @return Rgba color.
     */
    static inline Color colorFromNormalized(const Vec4<float>& normalizedColor)
    {
        Vec4<float> color = normalizedColor * 255.f;
        return rgbaColor(static_cast<uint8_t>(color.x),
                         static_cast<uint8_t>(color.y),
                         static_cast<uint8_t>(color.z),
                         static_cast<uint8_t>(color.w));
    }

    /**
     * @brief Get the System Color object
     * 
     * @param color 
     * @return System level color. 
     */
    static inline SDL_Color getSystemColor(Color color)
    {
        SDL_Color sysColor;
        sysColor.r = colorGetR(color);
        sysColor.g = colorGetG(color);
        sysColor.b = colorGetB(color);
        sysColor.a = colorGetA(color);
        
        return sysColor;
    }
}
