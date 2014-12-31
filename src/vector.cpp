#include <vector.hpp>

// Constructor.
cosmodon::vector::vector(number init_x, number init_y, number init_z, number init_w)
: x(init_x), y(init_y), z(init_z), w(init_w)
{
}

// Copy constructor.
cosmodon::vector::vector(cosmodon::vector &other) : vector()
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
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
    w = 1;
}

// Swap this vector with another vector.
void cosmodon::vector::swap(vector& other)
{
    std::swap(x, other.x);
    std::swap(y, other.y);
    std::swap(z, other.z);
    std::swap(w, other.w);
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
    return "(" + std::to_string(x)
      + ", " + std::to_string(y)
      + ", " + std::to_string(z)
      + ", " + std::to_string(w)
      + ")";
}

// Equivalency operator.
bool operator==(const cosmodon::vector &lhs, const cosmodon::vector &rhs)
{
    if (lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w) {
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

// Multiply a vector by a matrix.
cosmodon::vector operator*(const cosmodon::matrix &lhs, const cosmodon::vector &rhs)
{
    cosmodon::vector result;

    result.x = (lhs[0][0] * rhs.x) + (lhs[0][1] * rhs.y) + (lhs[0][2] * rhs.z) + (lhs[0][3] * rhs.w);
    result.y = (lhs[1][0] * rhs.x) + (lhs[1][1] * rhs.y) + (lhs[1][2] * rhs.z) + (lhs[1][3] * rhs.w);
    result.z = (lhs[2][0] * rhs.x) + (lhs[2][1] * rhs.y) + (lhs[2][2] * rhs.z) + (lhs[2][3] * rhs.w);
    result.x = (lhs[3][0] * rhs.x) + (lhs[3][1] * rhs.y) + (lhs[3][2] * rhs.z) + (lhs[3][3] * rhs.w);

    return result;
}

// Multiply a vector by a matrix, reverse order.
cosmodon::vector operator*(const cosmodon::vector &lhs, const cosmodon::matrix &rhs)
{
    return rhs * lhs;
}

// Output stream operator.
std::ostream& operator<<(std::ostream &stream, cosmodon::vector &value)
{
    stream << static_cast<std::string>(value);
    return stream;
}
