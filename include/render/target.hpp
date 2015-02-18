#ifndef COSMODON_RENDER_TARGET_HPP
#define COSMODON_RENDER_TARGET_HPP

#include "../color.hpp"
#include "graphic.hpp"
#include "../vertex.hpp"
#include "../transformation.hpp"

/**
 * Forward declarations, to resolve circular dependencies.
 */
namespace cosmodon
{
    class vertices;
    class graphic;
}

namespace cosmodon
{
    namespace render
    {
        /**
         * A rendering target.
         *
         * Rendering targets are able to render graphical information, even if they pass graphics
         * to other rendering targets: Windows are rendering targets, but pass graphics to a
         * rendering driver -- which are also rendering targets.
         */
        class target
        {
        public:
            /**
             * Render a collection of vertices.
             *
             * This is the primary method to render graphics. All other render() methods depend on
             * this.
             */
            virtual void render(const vertices *vertices, const matrix &transform, bool fill = true) = 0;

            /**
             * Render a collection of vertices.
             *
             * Retrieves the matrix from a transformation, and passes vertices to primary
             * rendering method.
             */
            virtual void render(const vertices *vertices, const transformation &transform);

            /**
             * Render a graphic.
             *
             * Provides this renderer to the object's render() method.
             */
            virtual void render(const cosmodon::graphic *object);

            /**
             * Clear the rendering area, using a color.
             *
             * Default color is black.
             */
            virtual void clear(const cosmodon::color color = cosmodon::black) = 0;
        };
    }
}

#endif
