#include <physics/distance.hpp>

// Calculates the distance between two positions.
cosmodon::number cosmodon::distance(cosmodon::vector &a, cosmodon::vector &b)
{
    return (a - b).magnitude();
}
