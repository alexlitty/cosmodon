#ifndef COSMODON_WINDOW
#define COSMODON_WINDOW

namespace cosmodon
{
    class window;
}

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
    class window
    {
    protected:
        // GLFW window handle.
        GLFWwindow* m_handle;

    public:
        /**
         * Constructor.
         */
        window();

        /**
         * Clear the window using a color.
         */
        void clear(cosmodon::color &color);

        /**
         * Render vertices to the window.
         */
        void render(cosmodon::primitive primitive, const float *vertices, uint32_t count);
    };
}

#endif
