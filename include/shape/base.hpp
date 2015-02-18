#ifndef COSMODON_SHAPE_BASE_HPP
#define COSMODON_SHAPE_BASE_HPP

#include "../vertex.hpp"
#include "../render/graphic.hpp"

namespace cosmodon
{
    namespace shape
    {
        /**
         * Base class for all shapes.
         */
        class base : public vertices, public graphic
        {
            // Fill mode.
            bool m_fill;

        public:
            // Render shape.
            virtual void render(render::target *object) const override;

            // Get position.
            virtual vector get_position() const override;

            // Get center.
            virtual vector get_center() const override;

            // Set fill mode.
            void set_fill(bool fill);
        };
    }
}

#endif
