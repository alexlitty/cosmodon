#ifndef COSMODON_WINDOW
#define COSMODON_WINDOW

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "color.hpp"
#include "component/canvas.hpp"
#include "primitive.hpp"

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

        // OpenGL Buffer.
        GLuint m_buffer;

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
        virtual void render(cosmodon::primitive primitive, const float *vertices, uint32_t count);
    };
}

#endif
