#ifndef COSMODON_COMPONENT_GRAPHIC
#define COSMODON_COMPONENT_GRAPHIC

#include "position.hpp"

/**
 * Forward declaration to resolve circular dependency.
 */
namespace cosmodon
{
    namespace component
    {
        class canvas;
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
         * Graphical component.
         *
         * Children objects are able to be rendered on a canvas object.
         */
        class graphic : public position
        {
        public:
            /**
             * Renders this graphic onto a canvas.
             */
            virtual void render(canvas &object) = 0;
        };
    }
}

/**
 * Include normal declarations of canvas.
 */
#include "canvas.hpp"

#endif
