#ifndef COSMODON_PHYSICS_DISTANCE_HPP
#define COSMODON_PHYSICS_DISTANCE_HPP

#include "../common/number.hpp"
#include "../component/position.hpp"
#include "../render/vector.hpp"

namespace cosmodon
{
    /**
     * Calculates the distance between two vectors.
     */
    number distance(vector &a, vector &b);
}

#endif
