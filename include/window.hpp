#ifndef COSMODON_WINDOW
#define COSMODON_WINDOW

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "color.hpp"

namespace cosmodon
{
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
    };
}

#endif
