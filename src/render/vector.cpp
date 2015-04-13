#include <render/vector.hpp>

// Constructor.
cosmodon::vector::vector(number init_x, number init_y, number init_z)
: x(init_x), y(init_y), z(init_z)
{
}

// Copy constructor.
cosmodon::vector::vector(const cosmodon::vector &other) : vector()
{
    x = other.x;
    y = other.y;
    z = other.z;
}

// Move constructor.
cosmodon::vector::vector(cosmodon::vector &&other) : vector()
{
    swap(other);
}

// Destructor.
cosmodon::vector::~vector()
{

}

// Resets this vector.
void cosmodon::vector::reset()
{
    x = 0;
    y = 0;
    z = 0;
}

// Swap this vector with another vector.
void cosmodon::vector::swap(vector& other)
{
    std::swap(x, other.x);
    std::swap(y, other.y);
    std::swap(z, other.z);
}

// Calculates vector magnitude.
cosmodon::number cosmodon::vector::magnitude() const
{
    return cosmodon::math::root(
        cosmodon::math::squared(x) + cosmodon::math::squared(y) + cosmodon::math::squared(z)
    );
}

// Returns a normalized version of this vector.
cosmodon::vector cosmodon::vector::normal() const
{
    cosmodon::number mag = magnitude();
    if (mag == 0) {
        return cosmodon::vector();
    }
    return cosmodon::vector(x / mag, y / mag, z / mag);
}

// Normalizes this vector.
void cosmodon::vector::normalize()
{
    *this = normal();
}

// Returns the dot product of two vectors.
cosmodon::number cosmodon::vector::dot(cosmodon::vector other) const
{
    return (x * other.x) + (y * other.y) + (z * other.z);
}

// Assignment to vector operator.
cosmodon::vector& cosmodon::vector::operator=(cosmodon::vector other)
{
    swap(other);
    return *this;
}

// Convert to string.
cosmodon::vector::operator std::string() const
{
    return "(" + std::to_string(x)
      + ", " + std::to_string(y)
      + ", " + std::to_string(z)
      + ")";
}

// Equivalency operator.
bool operator==(const cosmodon::vector &lhs, const cosmodon::vector &rhs)
{
    if (lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z) {
        return false;
    }
    return true;
}

// Inequivalency operator.
bool operator!=(const cosmodon::vector &lhs, const cosmodon::vector &rhs)
{
    return !(lhs == rhs);
}

// Addition operator.
cosmodon::vector operator+(const cosmodon::vector &lhs, const cosmodon::vector &rhs)
{
    return cosmodon::vector((lhs.x + rhs.x), (lhs.y + rhs.y), (lhs.z + rhs.z));
}

// Subtraction operator.
cosmodon::vector operator-(const cosmodon::vector &lhs, const cosmodon::vector &rhs)
{
    return cosmodon::vector((lhs.x - rhs.x), (lhs.y - rhs.y), (lhs.z - rhs.z));
}

// Multiply vectors by performing a cross-product.
cosmodon::vector operator*(const cosmodon::vector &lhs, const cosmodon::vector &rhs)
{
    cosmodon::vector result;

    result.x = (lhs.y * rhs.z) - (lhs.z * rhs.y);
    result.y = (lhs.z * rhs.x) - (lhs.x * rhs.z);
    result.z = (lhs.x * rhs.y) - (lhs.y * rhs.x);

    return result;
}

// Output stream operator.
std::ostream& operator<<(std::ostream &stream, const cosmodon::vector &value)
{
    stream << static_cast<const std::string>(value);
    return stream;
}
