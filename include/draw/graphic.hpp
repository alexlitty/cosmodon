#ifndef COSMODON_RENDER_GRAPHIC_HPP
#define COSMODON_RENDER_GRAPHIC_HPP

#include "canvas.hpp"
#include "../render/transformation.hpp"

/**
 * Forward declarations to resolve circular dependencies.
 */
namespace cosmodon
{
    class canvas;
}

/**
 * Normal declarations.
 */
namespace cosmodon
{
    /**
     * Base graphical object.
     *
     * Graphics are displayed on a canvas.
     */
    class graphic : public transformation
    {
    public:
        /**
         * Draws this graphic onto a canvas.
         */
        virtual void draw(canvas *target) const = 0;
    };
}

#endif
