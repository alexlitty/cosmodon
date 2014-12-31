#include <math.hpp>

// Value of pi.
double cosmodon::math::pi = ::acos(-1);

// Trigonometric sine.
double cosmodon::math::sine(double radians)
{
    return ::sin(radians);
}

// Trigonometric cosine.
double cosmodon::math::cosine(double radians)
{
    return cosmodon::math::sine(radians + (pi / 2));
}
