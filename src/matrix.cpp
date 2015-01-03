#include <matrix.hpp>

// Constructor.
cosmodon::matrix::matrix()
{
    m_values = new number[16];
    identity();
}

// Copy constructor.
cosmodon::matrix::matrix(const cosmodon::matrix &other)
{
    m_values = new number[16];
    for (uint8_t i = 0; i < 16; i++) {
        m_values[i] = other.m_values[i];
    }
}

// Move constructor.
cosmodon::matrix::matrix(cosmodon::matrix &&other)
{
    m_values = new number[16];
    swap(other);
}

// Destructor.
cosmodon::matrix::~matrix()
{
    delete [] m_values;
}

// Retrieve raw matrix values as an array.
cosmodon::number* cosmodon::matrix::raw()
{
    return m_values;
}

// Generates a matrix of zeroes.
void cosmodon::matrix::zero()
{
    for (uint8_t i = 0; i < 16; i++) {
        m_values[i] = 0;
    }
}

// Generates identity matrix.
void cosmodon::matrix::identity()
{
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            (*this)[i][j] = ((i == j) ? 1 : 0);
        }
    }
}

// Generate a translation matrix.
void cosmodon::matrix::translate(number x, number y, number z)
{
    identity();
    (*this)[0][3] = x;
    (*this)[1][3] = y;
    (*this)[2][3] = z;
}

// Generate a scaling matrix.
void cosmodon::matrix::scale(number x, number y, number z)
{
    identity();
    (*this)[0][0] = x;
    (*this)[1][1] = y;
    (*this)[2][2] = z;
}

// Generate a rotation matrix, about the x-axis.
void cosmodon::matrix::rotate_x(number radians)
{
    double sin = cosmodon::math::sine(radians);
    double cos = cosmodon::math::cosine(radians);

    identity();
    (*this)[1][1] = cos;
    (*this)[1][2] = -sin;
    (*this)[2][1] = sin;
    (*this)[2][2] = cos;
}

// Generate a rotation matrix, about the y-axis.
void cosmodon::matrix::rotate_y(number radians)
{
    double sin = cosmodon::math::sine(radians);
    double cos = cosmodon::math::cosine(radians);

    identity();
    (*this)[0][0] = cos;
    (*this)[0][2] = sin;
    (*this)[2][0] = -sin;
    (*this)[2][2] = cos;
}

// Generate a rotation matrix, about the z-axis.
void cosmodon::matrix::rotate_z(number radians)
{
    double sin = cosmodon::math::sine(radians);
    double cos = cosmodon::math::cosine(radians);

    identity();
    (*this)[0][0] = cos;
    (*this)[0][1] = -sin;
    (*this)[1][0] = sin;
    (*this)[1][1] = cos;
}

// Swap matrix.
void cosmodon::matrix::swap(matrix &other)
{
    for (uint8_t i = 0; i < 16; i++) {
        std::swap(m_values[i], other.m_values[i]);
    }
}

// Assignment to matrix operator.
cosmodon::matrix& cosmodon::matrix::operator=(matrix other)
{
    swap(other);
    return *this;
}

// Assignment to scalar operator.
cosmodon::matrix& cosmodon::matrix::operator=(cosmodon::number other)
{
    for (uint8_t i = 0; i < 16; i++) {
        m_values[i] = other;
    }
    return *this;
}

// Subscript operator.
cosmodon::number* cosmodon::matrix::operator[](uint8_t index)
{
    return &m_values[index*4];
}

// Subscript operator with const.
cosmodon::number* cosmodon::matrix::operator[](uint8_t index) const
{
    return &m_values[index*4];
}

// Convert matrix to string.
cosmodon::matrix::operator std::string()
{
    std::string result;

    for (uint8_t i = 0; i < 4; i++) {
        result += "[ ";
        for (uint8_t j = 0; j < 4; j++) {
            result += std::to_string((*this)[i][j]) + "; ";
        }

        // Remove extra comma and space.
        result.pop_back();
        result.pop_back();
        result += " ]\n";
    }

    // Remove extra newline.
    result.pop_back();
    return result;
}

// Equivalency operator.
bool operator==(cosmodon::matrix &lhs, cosmodon::matrix &rhs)
{
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            if (lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Inequivalency operator.
bool operator!=(cosmodon::matrix &lhs, cosmodon::matrix &rhs)
{
    return !(lhs == rhs);
}

// Addition operator.
cosmodon::matrix operator+(const cosmodon::matrix &A, const cosmodon::matrix &B)
{
    cosmodon::matrix result;
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Subtraction operator.
cosmodon::matrix operator-(const cosmodon::matrix &A, const cosmodon::matrix &B)
{
    cosmodon::matrix result;

    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }

    return result;
}

// Multiplication operator.
cosmodon::matrix operator*(const cosmodon::matrix &A, const cosmodon::matrix &B)
{
    cosmodon::matrix result;
    cosmodon::number sum;

    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            sum = 0;
            for (uint8_t k = 0; k < 4; k++) {
                sum += A[i][k] * B[k][j];
            }
            result[i][j] = sum;
        }
    }

    return result;
}

// Output stream operator.
std::ostream& operator<<(std::ostream &stream, cosmodon::matrix &value)
{
    stream << static_cast<std::string>(value);
    return stream;
}
