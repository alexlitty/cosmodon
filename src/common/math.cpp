#include <common/math.hpp>

// Value of pi.
double cosmodon::math::pi = ::acos(-1);

// Take the power of a value.
double cosmodon::math::power(double base, double exponent)
{
    return std::pow(base, exponent);
}

// Take the second power of a value.
double cosmodon::math::squared(double base)
{
    return cosmodon::math::power(base, 2);
}

// Take the root of a value.
double cosmodon::math::root(double base, double n)
{
    return cosmodon::math::power(base, 1 / n);
}

// Convert degrees to radians.
double cosmodon::math::radians(double degrees)
{
    return degrees * cosmodon::math::pi / 180.0f;
}

// Trigonometric sine.
double cosmodon::math::sine(double radians)
{
    return std::sin(radians);
}

// Trigonometric cosine.
double cosmodon::math::cosine(double radians)
{
    return std::cos(radians);
}

// Trigonometric tangent.
double cosmodon::math::tangent(double radians)
{
    return std::tan(radians);
}
