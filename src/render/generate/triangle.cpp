#include <render/generate.hpp>

// Generates an equilateral triangle.
void cosmodon::generate::triangle(cosmodon::vertices& v, cosmodon::number radius)
{
    v.add(radius, 0, 0);
    v.add(0, -radius, 0);
    v.add(0, radius, 0);
}
