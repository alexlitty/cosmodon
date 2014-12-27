#ifndef COSMODON_WINDOW
#define COSMODON_WINDOW

#include <string>

#include "rate.hpp"
#include "render/driver.hpp"
#include "render/opengl.hpp"

namespace cosmodon
{
    /**
     * A window, ideal to display a Cosmodon application.
     */
    class window : public render::target
    {
        /**
         * Copy constructor.
         *
         * Made private to prevent window copying.
         */
        window(window &copy);

    protected:
        // Rendering driver which created this window.
        render::driver *m_driver;

        // Frames per second calculator.
        mutable rate m_fps;

        // GLFW window handle. @@@
        GLFWwindow *m_handle;

    public:
        /**
         * Constructor.
         */
        window(render::driver *driver, GLFWwindow *handle);

        /**
         * Destructor.
         */
        ~window();

        /**
         * Clear window.
         */
        virtual void clear(color c = cosmodon::black);

        /**
         * Inherit render methods.
         */
        using cosmodon::render::target::render;

        /**
         * Render vertices to the window.
         */
        virtual void render(cosmodon::vertices *vertices) override;

        /**
         * Display rendered graphics on the window.
         */
        void display();
        
        /**
         * Retrieve current FPS.
         */
        uint16_t fps() const;
    };
}

#endif
