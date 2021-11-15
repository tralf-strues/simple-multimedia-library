/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file texture.cpp
 * @date 2021-09-20
 * 
 * @copyright Copyright (c) 2021
 */

#include <SDL_image.h>
#include "graphics_wrapper/texture.h"
#include "graphics_wrapper/renderer.h"

namespace Sml
{
    //------------------------------------------------------------------------------
    // Texture
    //------------------------------------------------------------------------------
    Texture::Texture(Renderer* renderer)
        : m_Renderer(renderer) {}

    Texture::Texture(Renderer* renderer, size_t width, size_t height)
        : m_Width(width),
        m_Height(height),
        m_Renderer(renderer),
        m_NativeTexture(nullptr) 
    {
        assert(m_Width);
        assert(m_Height);

        m_NativeTexture = SDL_CreateTexture(m_Renderer->getNativeRenderer(),
                                            SDL_PIXELFORMAT_RGBA8888, 
                                            SDL_TEXTUREACCESS_TARGET,
                                            m_Width, m_Height);
        SDL_SetTextureBlendMode(m_NativeTexture, SDL_BLENDMODE_BLEND);
    }

    Texture::~Texture()
    {
        if (m_NativeTexture != nullptr)
        {
            SDL_DestroyTexture(m_NativeTexture);
        }
    }

    size_t Texture::getWidth() const
    {
        return m_Width;
    }

    size_t Texture::getHeight() const
    {
        return m_Height;
    }

    Renderer* Texture::getRenderer() const
    {
        return m_Renderer;
    }

    SDL_Texture* Texture::getNativeTexture() const
    {
        return m_NativeTexture;
    }

    void Texture::readPixels(Color* dst) const
    {
        assert(dst);

        SDL_Texture* prevTarget = SDL_GetRenderTarget(m_Renderer->getNativeRenderer());

        SDL_SetRenderTarget(m_Renderer->getNativeRenderer(), m_NativeTexture);
        SDL_RenderReadPixels(m_Renderer->getNativeRenderer(), NULL, 0, dst, m_Width * sizeof(Color));
        SDL_SetRenderTarget(m_Renderer->getNativeRenderer(), prevTarget);
    }

    void Texture::copyTo(Texture* target,
                         const Rectangle<int32_t>* targetRegion,
                         const Rectangle<int32_t>* sourceRegion) const
    {
        Texture* savedTarget = m_Renderer->getTarget();
        m_Renderer->setTarget(target);

        renderTexture(m_Renderer, *this, targetRegion, sourceRegion);

        m_Renderer->setTarget(savedTarget);
    }

    bool Texture::writeToBMP(const char* filename) const
    {
        assert(filename);

        // uint32_t textureFormat = 0;
        // int32_t textureWidth = 0;
        // int32_t textureHeight = 0;

        // if (SDL_QueryTexture(m_NativeTexture, &textureFormat, nullptr, &textureWidth, &textureHeight) != 0)
        // {
        //     return false;
        // }

        // // FIXME: Use format!
        // SDL_Surface* surface = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);

        // Color* pixels = new Color[m_Width * m_Height * sizeof(Color)];

        // SDL_SetRenderTarget(renderer.getNativeRenderer(), m_NativeTexture);
        // SDL_RenderReadPixels(renderer.getNativeRenderer(), NULL, 0, pixels, m_Width * sizeof(Color));

        // SDL_Surface* surface = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
        // for (size_t i = 0; i < m_Width * m_Height; i++)
        // {
        //     ((uint8_t*)surface->pixels)[i * sizeof(Color) + 0] = colorGetB(pixels[i]);
        //     ((uint8_t*)surface->pixels)[i * sizeof(Color) + 1] = colorGetG(pixels[i]);
        //     ((uint8_t*)surface->pixels)[i * sizeof(Color) + 2] = colorGetR(pixels[i]);
        // }

        // if (SDL_SaveBMP(surface, filename) != 0)
        // {
        //     return false;
        // }

        // SDL_FreeSurface(surface);
        // delete[] pixels;

        return true;
    }

    bool Texture::loadFromImage(const char* filename)
    {
        assert(filename);

        SDL_Surface* surface = IMG_Load(filename);
        if (surface == nullptr)
        {
            return false;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer->getNativeRenderer(), surface);
        if (texture == nullptr)
        {
            SDL_FreeSurface(surface);
            return false;
        }

        if (m_NativeTexture != nullptr)
        {
            SDL_DestroyTexture(m_NativeTexture);
        }

        m_Width         = surface->w;
        m_Height        = surface->h;
        m_NativeTexture = texture;

        SDL_FreeSurface(surface);

        return true;

    }
    
    //------------------------------------------------------------------------------
    // BufferedTexture
    //------------------------------------------------------------------------------
    BufferedTexture::BufferedTexture(Renderer* renderer, size_t width, size_t height)
        : m_Texture(renderer, width, height),
        m_Buffer(new Color[width * height])
    {
    }

    BufferedTexture::BufferedTexture(Texture& texture)
        : m_Texture(texture),
        m_Buffer(new Color[m_Texture.getWidth() * m_Texture.getHeight()])
    {
        m_Texture.readPixels(m_Buffer);
    }

    BufferedTexture::~BufferedTexture()
    {
        if (m_Buffer != nullptr)
        {
            delete[] m_Buffer;
        }
    }

    Color* BufferedTexture::getBuffer()
    {
        return m_Buffer;
    }

    Texture& BufferedTexture::getTexture()
    {
        return m_Texture;
    }

    Color* BufferedTexture::operator[](size_t row)
    {
        assert(row < m_Texture.getHeight());

        return &m_Buffer[row * m_Texture.getWidth()];    
    }

    const Color* BufferedTexture::operator[](size_t row) const
    {
        assert(row < m_Texture.getHeight());

        return &m_Buffer[row * m_Texture.getWidth()];     
    }

    void BufferedTexture::clearBuffer(Color color)
    {
        size_t pixelsCount = m_Texture.getHeight() * m_Texture.getWidth();

        for (size_t i = 0; i < pixelsCount; i++)
        {
            m_Buffer[i] = color;
        }
    }

    void BufferedTexture::updateTexture()
    {
        SDL_UpdateTexture(m_Texture.getNativeTexture(),
                        nullptr,
                        static_cast<void*>(m_Buffer),
                        m_Texture.getWidth() * sizeof(Color));
    }

    void BufferedTexture::updateBuffer()
    {
        m_Texture.readPixels(m_Buffer);
    }
}