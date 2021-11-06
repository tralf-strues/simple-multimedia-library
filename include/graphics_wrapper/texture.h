/**
 * @brief Basic texture management.
 * 
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file texture.h
 * @date 2021-09-18
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <SDL.h>
#include "color.h"
#include "../sml_math.h"

namespace Sml
{
    class Renderer;

    class Texture
    {
    public:
        friend class BufferedTexture;

        Texture() = default;
        Texture(Renderer* renderer);
        Texture(Renderer* renderer, size_t width, size_t height);
        ~Texture();

        size_t       getWidth()             const;
        size_t       getHeight()            const;
        Renderer*    getRenderer()          const;
        SDL_Texture* getNativeTexture()     const;
        
        void         readPixels(Color* dst) const;

        /**
         * @brief Copies the sourceRegion of this Texture to the targetRegion of the target.
         * 
         * @param target 
         * @param targetRegion 
         * @param sourceRegion 
         */
        void copyTo(Texture* target,
                    const Rectangle<int32_t>* targetRegion,
                    const Rectangle<int32_t>* sourceRegion);

        // TODO: implement
        bool writeToBMP(const char* filename) const;
        bool loadFromImage(const char* filename);

    private:
        size_t        m_Width         = 0;
        size_t        m_Height        = 0;

        Renderer*     m_Renderer      = 0;
        SDL_Texture*  m_NativeTexture = 0;
    };

    class BufferedTexture
    {
    public:
        BufferedTexture(Renderer* renderer, size_t width, size_t height);
        BufferedTexture(Texture& texture);
        ~BufferedTexture();

        Color* getBuffer();
        Texture& getTexture();

        Color* operator[](size_t row);
        const Color* operator[](size_t row) const;

        void clearBuffer(Color color);
        
        /**
         * @brief Reflect buffer's changes on the texture.
         */
        void updateTexture();

        /**
         * @brief Reflect texture's changes (e.g. via Renderer) on the buffer.
         */
        void updateBuffer();

    private:
        Texture m_Texture;
        Color*  m_Buffer;
    };
}
