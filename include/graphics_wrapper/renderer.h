/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file renderer.h
 * @date 2021-09-11
 * 
 * @copyright Copyright (c) 2021
 */

#pragma once

#include <stdint.h>
#include <unordered_map>
#include <stack>
#include "window.h"
#include "texture.h"
#include "color.h"
#include "../sml_math.h"

namespace Sml
{
    class Renderer
    {
    public:
        enum Error
        {
            NO_ERROR     = 0,
            CREATE_ERROR = (1u << 0)
        };

        enum class BlendMode
        {
            NONE, BLEND
        };

        static constexpr Texture* WINDOW_TARGET = nullptr;

    public:
        /**
         * @brief Initializes Renderer with the specified window.
         * 
         * @note Supposed to be called once. All following calls will do nothing.
         * 
         * @param window
         */
        static void init(Window* window);

        /**
         * @return Renderer instance.
         */
        static Renderer& getInstance();

        /**
         * @return Whether or not Renderer::init() has been previously called.
         */
        static bool isInitialized();

    public:
        /**
         * @brief Destroy the Renderer object
         */
        ~Renderer();

        /**
         * @return Rendering color.
         */
        Color getColor() const;

        /**
         * @brief Set the rendering color.
         * @param color 
         */
        void setColor(Color color);

        /**
         * @return Current blending mode. 
         */
        BlendMode getBlendMode() const;

        /**
         * @brief Set the blending mode.
         * @param mode 
         */
        void setBlendMode(BlendMode mode);

        /**
         * @brief Get renderer's error status, which is represented as bit-mask of all
         *        possible Error codes.
         * 
         * @return Renderer's error status. 
         */
        uint32_t getError() const;

        /**
         * @return Renderer's current window.  
         */
        Window& getWindow() const;

        /**
         * @return Renderer's native renderer.
         */
        SDL_Renderer* getNativeRenderer() const;

        /**
         * @brief Present all rendered elements onto the renderer's target.
         */
        void present();
        
        /**
         * @brief Clear renderer's target with current rendering color.
         */
        void clear();

        /**
         * @brief Push current rendering target to stack.
         * 
         * Supposed to be used in conjunction with @ref popTarget() function. Useful if one
         * needs to save current rendering target before switching to then simply reset
         * target to the previous one using @ref popTarget().
         */
        void pushTarget();

        /**
         * @brief Sets current rendering target to the one currently on top of stack.
         * 
         * Supposed to be used in conjunction with @ref pushTarget() function.
         */
        void popTarget();

        /**
         * @brief Set rendering target.
         * 
         * @param targetTexture If WINDOW_TARGET, then set render target back to window.
         */
        void setTarget(Texture* targetTexture);

        /**
         * @brief Get rendering target.
         * 
         * @return Texture being the current rendering target, or WINDOW_TARGET, if the current
         *         rendering target is window.
         */
        Texture* getTarget();

        /**
         * @return The current target's width.
         */
        size_t getTargetWidth() const;

        /**
         * @return The current target's height.
         */
        size_t getTargetHeight() const;

        /**
         * @brief Allocate a pixel buffer and read pixels from the current target to it.
         * @warning The buffer must be freed after usage!
         * 
         * @param targetRegion If nullptr reads the entire surface.
         * 
         * @return Copy of the target's pixel buffer.
         */
        Color* readTargetPixels(const Rectangle<int32_t>* targetRegion = nullptr) const;

        /**
         * @brief Read pixels from the current target to dst.
         * @warning The pixel buffer must be of size greater or equal to the size of the window.
         * 
         * @param dst          Pixel buffer to read to.
         * @param targetRegion If nullptr reads the entire surface.
         */
        void readTargetPixelsTo(Color* dst, const Rectangle<int32_t>* targetRegion = nullptr) const;

        /**
         * @brief Updates the target surface's region 
         * 
         * @param src
         * @param region If nullptr update the entire surface.
         */
        void updateTargetPixels(const Color* src, const Rectangle<int32_t>* targetRegion = nullptr);

        /**
         * @brief Set rectangular clip region for the rendering target. Outside this region
         *        nothing will be rendered.
         * 
         * @param clipRegion 
         */
        void setClipRegion(const Rectangle<int32_t>& clipRegion) const;

        /**
         * @brief Disable the current clip region, if any was set using setClipRegion. 
         */
        void resetClipRegion() const;

        /**
         * @brief Render a single point on renderer's target at position pos.
         * 
         * @note If the point is outside rendering target's region, then it is simply ignored. 
         * 
         * @param pos Position of a point.
         */
        void renderPoint(const Vec2<int32_t>& pos);

        /**
         * @brief Render a line from start to end.
         * 
         * @note If a part of the line is outside rendering target's region, then this part
         *       is simply ignored.
         * 
         * @param start Position of line's start point.
         * @param end   Position of line's end point.
         */
        void renderLine(const Vec2<int32_t>& start, const Vec2<int32_t>& end);

        /**
         * @brief Render texture to the current rendering target in the region. Scales the
         *        texture if necessary.
         * 
         * @param source 
         * @param targetRegion 
         * @param sourceRegion 
         */
        void renderTexture(const Texture& source,
                           const Rectangle<int32_t>* targetRegion,
                           const Rectangle<int32_t>* sourceRegion);

        /**
         * @brief Render texture to the current rendering target at position pos.
         * 
         * @param texture 
         * @param pos 
         */
        void renderTexture(const Texture& texture, const Vec2<int32_t>& pos);

    private:
        static Renderer*   s_Instance;

        std::unordered_map<Window*, SDL_Renderer*> m_WindowSpecificNativeRenderers;
        SDL_Renderer*        m_NativeRenderer = nullptr;

        Window*              m_Window         = nullptr;
        Texture*             m_TargetTexture  = nullptr;
        std::stack<Texture*> m_TargetStack;
        
        uint32_t             m_ErrorStatus    = 0;

        /* Rendering state values. */
        Color                m_Color          = COLOR_BLACK;
        BlendMode            m_BlendMode      = BlendMode::BLEND;
        Rectangle<int32_t>   m_ClipRegion     = {0, 0, 0, 0};

    private:
        /**
         * @brief Construct a new Renderer object
         * 
         * @param window Renderer's target window.
         */
        Renderer(Window* window);

        /**
         * @brief Set the error.
         * 
         * @note New Renderer's error status = (prev error status) OR (error).
         * 
         * @param error Bit-mask based on Error codes.
         */
        void setError(uint32_t error);
    };

    /**
     * @brief See @ref Renderer::renderPoint().
     * 
     * @param pos 
     */
    void renderPoint(const Vec2<int32_t>& pos);

    /**
     * @brief See @ref Renderer::renderLine().
     * 
     * @param start 
     * @param end 
     */
    void renderLine(const Vec2<int32_t>& start, const Vec2<int32_t>& end);

    /**
     * @brief Render texture to the current rendering target in the region. Scales the
     *        texture if necessary.
     * 
     * @param source 
     * @param targetRegion 
     * @param sourceRegion 
     */
    void renderTexture(const Texture& source,
                       const Rectangle<int32_t>* targetRegion,
                       const Rectangle<int32_t>* sourceRegion);

    /**
     * @brief See @ref Renderer::renderTexture().
     * 
     * @param texture 
     * @param pos 
     */
    void renderTexture(const Texture& texture, const Vec2<int32_t>& pos);
}
