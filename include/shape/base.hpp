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
            virtual void render(render::target *object) override;
        };
    }
}

#endif
