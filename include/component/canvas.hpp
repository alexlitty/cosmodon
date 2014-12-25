#ifndef COSMODON_COMPONENT_CANVAS
#define COSMODON_COMPONENT_CANVAS

#include "../color.hpp"
#include "../clock.hpp"
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
            // Clock for calculating FPS.
            clock m_fps_clock;

        public:
            /**
             * Renders graphic, by pointer, onto this canvas.
             *
             * Calls the render() method of the graphic object.
             */
            void render(graphic *object);

            /**
             * Renders graphic, by reference, onto this canvas.
             *
             * Passed to the render(graphic *object) method.
             */
            void render(graphic &object);

            /**
             * Clear the entire canvas with a color.
             */
            virtual void clear(cosmodon::color &color) = 0;

            /**
             * Display currently rendered graphics.
             */
            virtual void display();
        };
    }
}

/**
 * Include normal decalaration of vertices.
 */
#include "../vertex.hpp"

#endif
