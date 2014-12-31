// Constructor.
template <uint8_t R, uint8_t C, typename T>
cosmodon::matrix<R, C, T>::matrix()
{
    m_values = new T[R * C];
    zero();
}

// Copy constructor.
template <uint8_t R, uint8_t C, typename T>
cosmodon::matrix<R, C, T>::matrix(cosmodon::matrix<R, C, T> &other)
{
    m_values = new T[R * C];
    for (uint8_t i = 0; i < R*C; i++) {
        m_values[i] = other.m_values[i];
    }
}

// Move constructor.
template <uint8_t R, uint8_t C, typename T>
cosmodon::matrix<R, C, T>::matrix(cosmodon::matrix<R, C, T> &&other)
{
    swap(other);
}

// Destructor.
template <uint8_t R, uint8_t C, typename T>
cosmodon::matrix<R, C, T>::~matrix()
{
    delete [] m_values;
}

// Generates a matrix of zeroes.
template <uint8_t R, uint8_t C, typename T>
void cosmodon::matrix<R, C, T>::zero()
{
    for (uint8_t i = 0; i < R*C; i++) {
        m_values[i] = 0;
    }
}

// Generates identity matrix.
template <uint8_t R, uint8_t C, typename T>
void cosmodon::matrix<R, C, T>::identity()
{
    if (R == C) {
        for (uint8_t i = 0; i < R; i++) {
            for (uint8_t j = 0; j < C; j++) {
                (*this)[i][j] = ((i == j) ? 1 : 0);
            }
        }
    }
}

// Generate a translation matrix.
template <uint8_t R, uint8_t C, typename T>
void cosmodon::matrix<R, C, T>::translate(T x, T y, T z)
{
    if (R == 4 && C == 4) {
        identity();
        (*this)[0][3] = x;
        (*this)[1][3] = y;
        (*this)[2][3] = z;
    }
}

// Generate a scaling matrix.
template <uint8_t R, uint8_t C, typename T>
void cosmodon::matrix<R, C, T>::scale(T x, T y, T z)
{
    if (R == 4 && C == 4) {
        identity();
        (*this)[0][0] = x;
        (*this)[1][1] = y;
        (*this)[2][2] = z;
    }
}

// Generate a rotation matrix, about the x-axis.
template <uint8_t R, uint8_t C, typename T>
void cosmodon::matrix<R, C, T>::rotate_x(T radians)
{
    if (R == 4 && C == 4) {
        double sin = cosmodon::math::sine(radians);
        double cos = cosmodon::math::cosine(radians);

        identity();
        (*this)[1][1] = cos;
        (*this)[1][2] = -sin;
        (*this)[2][1] = sin;
        (*this)[2][2] = cos;
    }
}

// Generate a rotation matrix, about the y-axis.
template <uint8_t R, uint8_t C, typename T>
void cosmodon::matrix<R, C, T>::rotate_y(T radians)
{
    if (R == 4 && C == 4) {
        double sin = cosmodon::math::sine(radians);
        double cos = cosmodon::math::cosine(radians);

        identity();
        (*this)[0][0] = cos;
        (*this)[0][2] = sin;
        (*this)[2][0] = -sin;
        (*this)[2][2] = cos;
    }
}

// Generate a rotation matrix, about the z-axis.
template <uint8_t R, uint8_t C, typename T>
void cosmodon::matrix<R, C, T>::rotate_z(T radians)
{
    if (R == 4 && C == 4) {
        double sin = cosmodon::math::sine(radians);
        double cos = cosmodon::math::cosine(radians);

        identity();
        (*this)[0][0] = cos;
        (*this)[0][1] = -sin;
        (*this)[1][0] = sin;
        (*this)[1][1] = cos;
    }
}

// Swap matrix.
template <uint8_t R, uint8_t C, typename T>
void cosmodon::matrix<R, C, T>::swap(matrix<R, C, T> &other)
{
    for (uint8_t i = 0; i < R*C; i++) {
        std::swap(m_values[i], other.m_values[i]);
    }
}

// Assignment to matrix operator.
template <uint8_t R, uint8_t C, typename T>
cosmodon::matrix<R, C, T>& cosmodon::matrix<R, C, T>::operator=(matrix<R, C, T> other)
{
    swap(other);
    return *this;
}

// Assignment to scalar operator.
template<uint8_t R, uint8_t C, typename T>
cosmodon::matrix<R, C, T>& cosmodon::matrix<R, C, T>::operator=(T other)
{
    for (uint8_t i = 0; i < R*C; i++) {
        m_values[i] = other;
    }
    return *this;
}

// Subscript operator.
template <uint8_t R, uint8_t C, typename T>
T* cosmodon::matrix<R, C, T>::operator[](uint8_t index)
{
    return &m_values[index*C];
}

// Subscript operator with const.
template <uint8_t R, uint8_t C, typename T>
T* cosmodon::matrix<R, C, T>::operator[](uint8_t index) const
{
    return &m_values[index*C];
}

// Convert matrix to string.
template <uint8_t R, uint8_t C, typename T>
cosmodon::matrix<R, C, T>::operator std::string()
{
    std::string result;

    for (uint8_t i = 0; i < R; i++) {
        result += "[ ";
        for (uint8_t j = 0; j < C; j++) {
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
