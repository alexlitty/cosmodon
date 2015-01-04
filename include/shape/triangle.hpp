#ifndef COSMODON_SHAPE_TRIANGLE
#define COSMODON_SHAPE_TRIANGLE

#include "../render.hpp"
#include "../transformation.hpp"

namespace cosmodon
{
    namespace shape
    {
        class triangle : public graphic
        {
            // Vertices which compose a triangle.
            vertices m_vertices;

        public:
            /**
             * Constructor.
             */
            triangle();

            /**
             * Render this triangle.
             */
            void render(render::target *target);
        };
    }
}

#endif
