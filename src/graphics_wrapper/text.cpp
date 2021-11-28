/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file text.cpp
 * @date 2021-10-04
 * 
 * @copyright Copyright (c) 2021
 */

#include "graphics_wrapper/text.h"

namespace Sml
{
    Font::Font(const char* filename, size_t size) : m_FontSize(size)
    {
        if (filename != nullptr)
        {
            m_NativeFont = TTF_OpenFont(filename, size);
            assert(m_NativeFont);
        }
    }

    Font::Font() : m_NativeFont(nullptr), m_FontSize(0) {}

    TTF_Font* Font::getNativeFont() const
    {
        return m_NativeFont;
    }

    size_t Font::getSize() const 
    {
        return m_FontSize;
    }

    Text::Text(const Font& font, const char* str, Color color)
        : m_Font(font), m_Str(str), m_Color(color) {}

    Text::~Text()
    {
        destroy();
    }

    Vec2<int32_t> Text::estimateTextDimensions(const char* text) const
    {
        assert(text);

        Vec2<int32_t> dimensions{0, 0};
        TTF_SizeText(getFont().getNativeFont(), text, &dimensions.x, &dimensions.y);

        return dimensions;
    }

    const Font& Text::getFont()      const { return m_Font;      }
    const char* Text::getStr()       const { return m_Str;       }
    Color       Text::getColor()     const { return m_Color;     }
    size_t      Text::getWidth()     const { return m_Width;     }
    size_t      Text::getHeight()    const { return m_Height;    }
    size_t      Text::getWrapWidth() const { return m_WrapWidth; }

    void Text::setFont(const Font& font)      { m_Font      = font;      }
    void Text::setColor(Color color)          { m_Color     = color;     }
    void Text::setString(const char* str)     { m_Str       = str;       }
    void Text::setWrapWidth(size_t wrapWidth) { m_WrapWidth = wrapWidth; }

    void Text::load()
    {
        assert(m_Font.getNativeFont());
        assert(m_Font.getSize() > 0);
        assert(m_Str);

        destroy();

        SDL_Surface* loadedSurface = nullptr;
        if (m_WrapWidth != 0)
        {
            loadedSurface = TTF_RenderText_Blended_Wrapped(m_Font.getNativeFont(),
                                                           m_Str,
                                                           getSystemColor(m_Color),
                                                           m_WrapWidth);
        }
        else
        {
            loadedSurface = TTF_RenderText_Blended(m_Font.getNativeFont(),
                                                   m_Str,
                                                   getSystemColor(m_Color));
        }

        assert(loadedSurface);

        m_Texture = SDL_CreateTextureFromSurface(Renderer::getInstance().getNativeRenderer(), loadedSurface);
        assert(m_Texture);
        
        m_Width  = loadedSurface->w;
        m_Height = loadedSurface->h;

        SDL_FreeSurface(loadedSurface);
    }

    void Text::destroy()
    {
        if (m_Texture != nullptr)
        {
            SDL_DestroyTexture(m_Texture);
        }
    }

    void Text::render(const Vec2<int32_t>& pos) const
    {
        SDL_Rect renderQuad = {pos.x, pos.y, static_cast<int32_t>(m_Width), static_cast<int32_t>(m_Height)};
        
        SDL_RenderCopy(Renderer::getInstance().getNativeRenderer(), m_Texture, nullptr, &renderQuad); 
    }
}