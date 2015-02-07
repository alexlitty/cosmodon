#ifndef COSMODON_SHAPE_PYRAMID_HPP
#define COSMODON_SHAPE_PYRAMID_HPP

#include "../render.hpp"
#include "../vector.hpp"
#include "base.hpp"

namespace cosmodon
{
    namespace shape
    {
        class pyramid : public shape::base
        {
        public:
            /**
             * Constructor.
             */
            pyramid(number width, number height);
        };
    }
}

#endif
