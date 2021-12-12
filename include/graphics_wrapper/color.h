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
#include <algorithm>
#include "../math/vec4.h"

namespace Sml
{
    struct ColorHsv
    {
        float h = 0; ///< Ranging from 0 to 359 (in degrees)
        float s = 0; ///< Ranging from 0 to 1
        float v = 0; ///< Ranging from 0 to 1
        float a = 0; ///< Ranging from 0 to 1
    };

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
     * @brief Sets color's red chanel to r.
     * 
     * @param color
     * @param r
     * @return New color.
     */
    static inline Color colorSetR(Color color, uint8_t r)
    {
        return (color & ~(0xFF << 24u)) | ((uint32_t) r << 24u);
    }

    /**
     * @brief Sets color's green chanel to g.
     * 
     * @param color
     * @param g
     * @return New color.
     */
    static inline Color colorSetG(Color color, uint8_t g)
    {
        return (color & ~(0xFF << 16u)) | ((uint32_t) g << 16u);
    }

    /**
     * @brief Sets color's blue chanel to b.
     * 
     * @param color
     * @param b
     * @return New color.
     */
    static inline Color colorSetB(Color color, uint8_t b)
    {
        return (color & ~(0xFF << 8u)) | ((uint32_t) b << 8u);
    }

    /**
     * @brief Sets color's alpha chanel to a.
     * 
     * @param color
     * @param a
     * @return New color.
     */
    static inline Color colorSetA(Color color, uint8_t a)
    {
        return (color & ~(0xFF)) | ((uint32_t) a);
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
     * @brief Convert color from HSV to RGB (supporting alpha channel).
     * 
     * @param hsv
     * 
     * @return Color in rgba. 
     */
    static inline Color convertHsvToRgb(const ColorHsv& hsv)
    {
        assert(hsv.h >= 0 && hsv.h <= 360);
        assert(hsv.s >= 0 && hsv.s <= 1);
        assert(hsv.v >= 0 && hsv.v <= 1);
        assert(hsv.a >= 0 && hsv.a <= 1);

        float C = hsv.s * hsv.v;
        float X = C * (1 - fabs(fmod(hsv.h / 60, 2) - 1));
        float m = hsv.v - C;
        
        Vec4f rgb;

        if (hsv.h >= 0 && hsv.h < 60)
        {
            rgb = {C, X, 0, hsv.a};
        }
        else if (hsv.h >= 60 && hsv.h < 120)
        {
            rgb = {X, C, 0, hsv.a};
        }
        else if (hsv.h >= 120 && hsv.h < 180)
        {
            rgb = {0, C, X, hsv.a};
        }
        else if (hsv.h >= 180 && hsv.h < 240)
        {
            rgb = {0, X, C, hsv.a};
        }
        else if (hsv.h >= 240 && hsv.h < 300)
        {
            rgb = {X, 0, C, hsv.a};
        }
        else
        {
            rgb = {C, 0, X, hsv.a};
        }

        rgb += {m, m, m, 0};

        return colorFromNormalized(rgb);
    }

    /**
     * @brief Convert color from RGB to HSV (supporting alpha channel).
     * 
     * @param rgba
     * 
     * @return Color in hsv.
     */
    static inline ColorHsv convertRgbToHsv(Color rgba)
    {
        Vec4f fColor = colorToNormalized(rgba);
        ColorHsv hsv;

        float cMax = std::max(std::max(fColor.x, fColor.y), fColor.z);
        float cMin = std::min(std::min(fColor.x, fColor.y), fColor.z);
        float delta = cMax - cMin;
        
        if (delta > 0)
        {
            if (cMax == fColor.x)
            {
                hsv.h = 60 * (fmod(((fColor.y - fColor.z) / delta), 6));
            }
            else if (cMax == fColor.y)
            {
                hsv.h = 60 * (((fColor.z - fColor.x) / delta) + 2);
            }
            else if (cMax == fColor.z)
            {
                hsv.h = 60 * (((fColor.x - fColor.y) / delta) + 4);
            }
            
            if (cMax > 0)
            {
                hsv.s = delta / cMax;
            }
            else
            {
                hsv.s = 0;
            }
            
            hsv.v = cMax;
        }
        else
        {
            hsv.h = 0;
            hsv.s = 0;
            hsv.v = cMax;
        }
        
        if (hsv.h < 0)
        {
            hsv.h = 360 + hsv.h;
        }

        hsv.a = fColor.w;

        return hsv;
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
