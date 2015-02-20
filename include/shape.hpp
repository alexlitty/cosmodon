#ifndef COSMODON_SHAPE_HPP
#define COSMODON_SHAPE_HPP

#include "vertex.hpp"

namespace cosmodon
{
    /**
     * A collection of shape generation methods.
     *
     * All methods overwrite the required vertices method.
     */
    namespace shape
    {
        void pyramid(vertices &v, number width, number height);
    }
}

#endif
