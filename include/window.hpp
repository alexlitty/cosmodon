#ifndef COSMODON_WINDOW
#define COSMODON_WINDOW

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

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
    };
}

#endif
