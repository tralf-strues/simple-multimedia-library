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
    Texture::Texture(size_t width, size_t height)
        : m_Width(width), m_Height(height), m_NativeTexture(nullptr) 
    {
        assert(m_Width);
        assert(m_Height);

        m_NativeTexture = SDL_CreateTexture(Renderer::getInstance().getNativeRenderer(),
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

    SDL_Texture* Texture::getNativeTexture() const
    {
        return m_NativeTexture;
    }

    Color* Texture::readPixels(const Rectangle<int32_t>* region) const
    {
        Rectangle<int32_t> realRegion = (region != nullptr) ?
                                        *region :
                                        Rectangle<int32_t>{{0, 0},
                                                           static_cast<int32_t>(getWidth()),
                                                           static_cast<int32_t>(getHeight())};

        if (realRegion.width <= 0 || realRegion.height <= 0)
        {
            return nullptr;
        }

        Color* pixels = new Color[realRegion.width * realRegion.height];
        readPixelsTo(pixels);

        return pixels;
    }

    void Texture::readPixelsTo(Color* dst, const Rectangle<int32_t>* region) const
    {
        assert(dst);

        SDL_Rect rect;
        if (region != nullptr)
        {
            rect = toNativeRectangle(*region);
        }

        SDL_Texture* prevTarget = SDL_GetRenderTarget(Renderer::getInstance().getNativeRenderer());

        SDL_SetRenderTarget(Renderer::getInstance().getNativeRenderer(), m_NativeTexture);

        SDL_RenderReadPixels(Renderer::getInstance().getNativeRenderer(),
                             region == nullptr ? nullptr : &rect,
                             0,
                             dst,
                             (region == nullptr ? static_cast<int32_t>(m_Width) : rect.w) * sizeof(Color));
        
        SDL_SetRenderTarget(Renderer::getInstance().getNativeRenderer(), prevTarget);
    }

    void Texture::updatePixels(const Color* src, const Rectangle<int32_t>* region)
    {
        assert(src);

        SDL_Rect rect;
        if (region != nullptr)
        {
            rect = toNativeRectangle(*region);
        }

        SDL_UpdateTexture(getNativeTexture(),
                          region == nullptr ? nullptr : &rect,
                          static_cast<const void*>(src),
                          (region == nullptr ? static_cast<int32_t>(m_Width) : rect.w) * sizeof(Color));
    }

    void Texture::copyTo(Texture* target,
                         const Rectangle<int32_t>* targetRegion,
                         const Rectangle<int32_t>* sourceRegion) const
    {
        Texture* savedTarget = Renderer::getInstance().getTarget();
        Renderer::getInstance().setTarget(target);

        renderTexture(*this, targetRegion, sourceRegion);

        Renderer::getInstance().setTarget(savedTarget);
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

        SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::getInstance().getNativeRenderer(), surface);
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
    BufferedTexture::BufferedTexture(size_t width, size_t height)
        : m_Texture(width, height), m_Buffer(new Color[width * height]) { }

    BufferedTexture::BufferedTexture(Texture& texture)
        : m_Texture(texture), m_Buffer(new Color[m_Texture.getWidth() * m_Texture.getHeight()])
    {
        m_Texture.readPixelsTo(m_Buffer);
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
        m_Texture.readPixelsTo(m_Buffer);
    }
}