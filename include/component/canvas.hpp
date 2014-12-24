#ifndef COSMODON_COMPONENT_CANVAS
#define COSMODON_COMPONENT_CANVAS

#include "../color.hpp"
#include "../primitive.hpp"
#include "graphic.hpp"

/**
 * Forward declarations to resolve circular dependencies.
 */
namespace cosmodon
{
    class vertices;
    
    namespace component
    {
        class graphic;
    }
}

/**
 * Normal declarations.
 */
namespace cosmodon
{
    namespace component
    {
        /**
         * Canvas component.
         *
         * Children classes are able to render graphical objects.
         */
        class canvas
        {
        public:
            /**
             * Renders a raw array of vertices onto this canvas.
             *
             * All render() methods are dependent of this method.
             */
            virtual void render(cosmodon::primitive primitive, const float *vertices, uint32_t count) = 0;

            /**
             * Renders graphic, by pointer, onto this canvas.
             *
             * Calls the render() method of the graphic object.
             */
            virtual void render(graphic *object);

            /**
             * Renders graphic, by reference, onto this canvas.
             *
             * Passed to the render(graphic *object) method.
             */
            virtual void render(graphic &object);

            /**
             * Clear the entire canvas with a color.
             */
            virtual void clear(cosmodon::color &color) = 0;
        };
    }
}

/**
 * Include normal decalaration of vertices.
 */
#include "../vertex.hpp"

#endif
