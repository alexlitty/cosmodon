#ifndef COSMODON_SHAPE_TRIANGLE
#define COSMODON_SHAPE_TRIANGLE

#include "component/graphic.hpp"

namespace cosmodon
{
    namespace shape
    {
        class triangle : public component::graphic
        {
            // Vertices which compose a triangle.
            vertices m_vertices;

        public:
            /**
             * Constructor.
             */
            triangle();

            /**
             * Render this triangle to a canvas.
             */
            void render(component::canvas &object);
        };
    }
}

#endif
