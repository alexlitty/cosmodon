#ifndef COSMODON_WINDOW
#define COSMODON_WINDOW

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "clock.hpp"
#include "color.hpp"
#include "component/canvas.hpp"
#include "primitive.hpp"
#include "rate.hpp"

namespace cosmodon
{
    /**
     * A window, ideal to display a Cosmodon application.
     */
    class window : public component::canvas
    {
    protected:
        // GLFW window handle.
        GLFWwindow *m_handle;

        // OpenGL buffers.
        GLuint m_buffer_positions;
        GLuint m_buffer_colors;

        // Frames per second calculator.
        mutable rate m_fps;

    public:
        /**
         * Constructor.
         */
        window();

        /**
         * Destructor.
         */
        ~window();

        /**
         * Clear the window using a color.
         */
        void clear(cosmodon::color &color);

        /**
         * Inherit render methods.
         */
        using component::canvas::render;

        /**
         * Render vertices to the window.
         */
        virtual void render(cosmodon::vertices &vertices);

        /**
         * Display rendered graphics on the window.
         */
        virtual void display() override;
        
        /**
         * Retrieve current FPS.
         */
        uint16_t fps() const;
    };
}

#endif
