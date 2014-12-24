#ifndef COSMODON_COMPONENT_GRAPHIC
#define COSMODON_COMPONENT_GRAPHIC

#include "canvas.hpp"
#include "position.hpp"

namespace cosmodon
{
    namespace component
    {
        /**
         * Forward declarations.
         *
         * Resolves circular dependencies between canvas and graphic components.
         */
        class canvas;

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

#endif
