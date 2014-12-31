#include <vector.hpp>

// Constructor.
cosmodon::vector::vector(number init_x, number init_y, number init_z)
: x(init_x), y(init_y), z(init_z)
{
}

// Copy constructor.
cosmodon::vector::vector(cosmodon::vector &other) : vector()
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

// Assignment to vector operator.
cosmodon::vector& cosmodon::vector::operator=(cosmodon::vector other)
{
    swap(other);
    return *this;
}

// Convert to string.
cosmodon::vector::operator std::string()
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
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

// Output stream operator.
std::ostream& operator<<(std::ostream &stream, cosmodon::vector &value)
{
    stream << static_cast<std::string>(value);
    return stream;
}
