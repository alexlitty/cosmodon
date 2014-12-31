#ifndef COSMODON_MATH_HPP
#define COSMODON_MATH_HPP

#include <math.h>

namespace cosmodon
{
    namespace math
    {
        // Value of pi.
        extern double pi;

        // Trigonometric sine.
        double sine(double radians);

        // Trigonometric cosine.
        double cosine(double radians);
    }
}

#endif
