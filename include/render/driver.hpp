#ifndef COSMODON_RENDER_DRIVER_HPP
#define COSMODON_RENDER_DRIVER_HPP

#include "shader.hpp"
#include "target.hpp"

/**
 * Forward declarations to resolve circular dependencies.
 */
namespace cosmodon
{
    class window;
}

/**
 * Normal declarations.
 */
namespace cosmodon
{
    namespace render
    {
        /**
         * A driver to render graphics.
         */
        class driver : public target
        {
        public:
            /**
             * Creates a window.
             *
             * Throws a Cosmodon exception upon error.
             */
            virtual cosmodon::window* create_window(std::string title, uint16_t width, uint16_t height) = 0;

            /**
             * Set shaders to be used when rendering.
             *
             * Pass a null pointer to disable a shader.
             *
             * Returns false if one or more shaders could not be used.
             */
            virtual bool set_shaders(cosmodon::shader *vertex, cosmodon::shader *fragment, cosmodon::shader *geometry) = 0;
        };
    }
}

// @@@
#include "window.hpp"

#endif
