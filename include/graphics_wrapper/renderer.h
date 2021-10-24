//------------------------------------------------------------------------------
//! @author Nikita Mochalov (github.com/tralf-strues)
//! @file renderer.h
//! @date 2021-09-11
//! 
//! @copyright Copyright (c) 2021
//------------------------------------------------------------------------------

#ifndef RENDERER_H
#define RENDERER_H

#include <stdint.h>
#include "window.h"
#include "texture.h"
#include "color.h"
#include "../sml_math.h"

struct Rectangle
{
    Vec2<int32_t> pos;
    
    int32_t width;
    int32_t height;
};

class Renderer
{
public:
    enum Error
    {
        NO_ERROR     = 0,
        CREATE_ERROR = (1u << 0)
    };

public:
    //--------------------------------------------------------------------------
    //! @brief Construct a new Renderer object.
    //! 
    //! @param window Renderer's target window.
    //--------------------------------------------------------------------------
    Renderer(Window& window);

    //--------------------------------------------------------------------------
    //! @brief Destroy the Renderer object.
    //--------------------------------------------------------------------------
    ~Renderer();

    //--------------------------------------------------------------------------
    //! @return Rendering color. 
    //--------------------------------------------------------------------------
    Color getColor() const;

    //--------------------------------------------------------------------------
    //! @brief Set the rendering color.
    //! 
    //! @param color 
    //--------------------------------------------------------------------------
    void setColor(Color color);

    //--------------------------------------------------------------------------
    //! @brief Get renderer's error status, which is represented as bit-mask of
    //!        all possible Error codes.
    //! 
    //! @return Renderer's error status.
    //--------------------------------------------------------------------------
    uint32_t getError() const;

    //--------------------------------------------------------------------------
    //! @return Renderer's target window. 
    //--------------------------------------------------------------------------
    Window& getWindow() const;

    //--------------------------------------------------------------------------
    //! @return Renderer's native renderer. 
    //--------------------------------------------------------------------------
    SDL_Renderer* getNativeRenderer() const;

    //--------------------------------------------------------------------------
    //! @brief Present all rendered elements onto the renderer's target window.
    //--------------------------------------------------------------------------
    void present() const;
    
    //--------------------------------------------------------------------------
    //! @brief Clear renderer's target with current rendering color.
    //--------------------------------------------------------------------------
    void clear();

    //--------------------------------------------------------------------------
    //! @brief Set rendering target.
    //! 
    //! @param targetTexture If nullptr, then set render target back to window.
    //--------------------------------------------------------------------------
    void setTarget(Texture* targetTexture);

    //--------------------------------------------------------------------------
    //! @brief Get rendering target.
    //! 
    //! @return Texture being the current rendering target, or nullptr, if the
    //!         current rendering target is window.
    //--------------------------------------------------------------------------
    Texture* getTarget();

    //--------------------------------------------------------------------------
    //! @brief Set rectangular clip region for the rendering target. Outside 
    //!        this region nothing will be rendered.
    //! 
    //! @param clipRegion
    //--------------------------------------------------------------------------
    void setClipRegion(const Rectangle& clipRegion) const;

    //--------------------------------------------------------------------------
    //! @brief Disable the current clip region, if any was set using 
    //!        setClipRegion.
    //--------------------------------------------------------------------------
    void resetClipRegion() const;

    //--------------------------------------------------------------------------
    //! @brief Render a single point on renderer's target at position pos.
    //! 
    //! @note If the point is outside rendering target's region, then it is 
    //!       simply ignored. 
    //! 
    //! @param pos Position of a point.
    //--------------------------------------------------------------------------
    void renderPoint(const Vec2<int32_t>& pos);

    //--------------------------------------------------------------------------
    //! @brief Render a line from start to end.
    //! 
    //! @note If a part of the line is outside rendering target's region, then 
    //!       this part is simply ignored.
    //! 
    //! @param start Position of line's start point.
    //! @param end   Position of line's end point.
    //--------------------------------------------------------------------------
    void renderLine(const Vec2<int32_t>& start, const Vec2<int32_t>& end);

    //--------------------------------------------------------------------------
    //! @brief Render texture to the current rendering target in the region.
    //!        Scales the texture if necessary.
    //! 
    //! @param texture
    //! @param region 
    //--------------------------------------------------------------------------
    void renderTexture(const Texture& texture, const Rectangle& region);

    //--------------------------------------------------------------------------
    //! @brief Render texture to the current rendering target at position pos.
    //! 
    //! @param texture 
    //! @param pos 
    //--------------------------------------------------------------------------
    void renderTexture(const Texture& texture, const Vec2<int32_t>& pos);

private:
    Window&       m_Window;
    Texture*      m_TargetTexture  = nullptr;
    Color         m_Color          = COLOR_BLACK;
    uint32_t      m_ErrorStatus    = 0;

    SDL_Renderer* m_NativeRenderer = nullptr;

    //--------------------------------------------------------------------------
    //! @brief Set the error.
    //! 
    //! @note New Renderer's error status = (prev error status) OR (error).
    //! 
    //! @param error Bit-mask based on Error codes.
    //--------------------------------------------------------------------------
    void setError(uint32_t error);
};

//------------------------------------------------------------------------------
//! @brief See @ref Renderer::renderPoint().
//! 
//! @param renderer 
//! @param pos 
//------------------------------------------------------------------------------
void renderPoint(Renderer& renderer, const Vec2<int32_t>& pos);

//------------------------------------------------------------------------------
//! @brief See @ref Renderer::renderLine().
//! 
//! @param renderer 
//! @param start 
//! @param end 
//------------------------------------------------------------------------------
void renderLine(Renderer& renderer, const Vec2<int32_t>& start, const Vec2<int32_t>& end);

//------------------------------------------------------------------------------
//! @brief Render texture to the current rendering target in the region.
//!        Scales the texture if necessary.
//! 
//! @param renderer 
//! @param texture
//! @param region 
//------------------------------------------------------------------------------
void renderTexture(Renderer& renderer, const Texture& texture, const Rectangle& region);

//------------------------------------------------------------------------------
//! @brief See @ref Renderer::renderTexture().
//!
//! @param renderer 
//! @param texture 
//! @param pos 
//------------------------------------------------------------------------------
void renderTexture(Renderer& renderer, const Texture& texture, const Vec2<int32_t>& pos);

#endif // RENDERER_H