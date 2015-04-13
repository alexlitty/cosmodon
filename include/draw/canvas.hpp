#ifndef COSMODON_RENDER_TARGET_HPP
#define COSMODON_RENDER_TARGET_HPP

#include "../render/color.hpp"
#include "graphic.hpp"
#include "../render/vertex.hpp"
#include "../render/transformation.hpp"

namespace cosmodon
{
    class vertices;
    class graphic;
}

namespace cosmodon
{
    /**
     * A canvas to draw into.
     *
     * Canvases display graphical information.
     */
    class canvas
    {
    public:
        /**
         * Draw a collection of vertices.
         *
         * This is the primary method to render graphics. All other render() methods depend on
         * this.
         */
        virtual void draw(const vertices *vertices, const matrix &transform, bool fill = true) = 0;

        /**
         * Draw a collection of vertices.
         *
         * Retrieves the matrix from a transformation, and passes vertices to primary
         * rendering method.
         */
        virtual void draw(const vertices *vertices, const transformation &transform);

        /**
         * Draw a graphic.
         *
         * Provides this renderer to the object's render() method.
         */
        virtual void draw(const cosmodon::graphic *object);

        /**
         * Clear the rendering area, using a color.
         *
         * Default color is black.
         */
        virtual void clear(const cosmodon::color color = cosmodon::black) = 0;
    };
}

#endif
