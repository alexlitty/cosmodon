#ifndef COSMODON_MATH_HPP
#define COSMODON_MATH_HPP

#include <cmath>

namespace cosmodon
{
    namespace math
    {
        // Value of pi.
        extern double pi;

        // Take the power of a value.
        double power(double base, double exponent);

        // Take the second power of a value.
        double squared(double base);

        // Take the root of a value.
        double root(double base, double n = 2);

        // Trigonometric sine.
        double sine(double radians);

        // Trigonometric cosine.
        double cosine(double radians);

        // Trigonometric tangent.
        double tangent(double radians);
    }
}

#endif
