#ifndef COSMODON_RENDER_DRIVER_HPP
#define COSMODON_RENDER_DRIVER_HPP

#include "../common/rate.hpp"
#include "shader.hpp"
#include "canvas.hpp"

namespace cosmodon
{
    namespace draw
    {
        /**
         * A driver to render graphics.
         *
         * Responsible for creating a single window.
         */
        class driver : public canvas
        {
        protected:
            mutable rate m_fps;

        public:
            /**
             * Set shaders to be used when rendering.
             *
             * Pass a null pointer to disable a shader.
             *
             * Returns false if one or more shaders could not be used.
             */
            virtual bool set_shaders(cosmodon::shader *vertex, cosmodon::shader *fragment, cosmodon::shader *geometry) = 0;

            /**
             * Display rendered objects.
             */
            virtual void display() = 0;

            /**
             * Retrieve frames per second.
             */
            virtual uint32_t get_fps() const;
        };
    }
}

#endif
