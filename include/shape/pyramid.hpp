#ifndef COSMODON_SHAPE_PYRAMID_HPP
#define COSMODON_SHAPE_PYRAMID_HPP

#include "../render.hpp"
#include "../vector.hpp"

namespace cosmodon
{
    namespace shape
    {
        class pyramid : public graphic
        {
        protected:
            // Internal vertices.
            vertices m_vertices;

        public:
            /**
             * Constructor.
             */
            pyramid(number width, number height);

            /**
             * Render pyramid.
             */
            virtual void render(render::target *target) override;

            /**
             * Get pyramid position.
             */
            virtual vector get_position();
        };
    }
}

#endif
