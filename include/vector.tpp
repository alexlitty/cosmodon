/**
 * Templated vector definitions.
 */

// Constructor.
template <uint8_t N, typename T>
cosmodon::vector<N, T>::vector()
{
    m_values = new T[N];
    reset();
}

// Copy constructor.
template <uint8_t N, typename T>
cosmodon::vector<N, T>::vector(cosmodon::vector<N, T> &other) : vector()
{
    for (uint8_t i = 0; i < N; i++) {
        m_values[i] = other[i];
    }
}

// Move constructor.
template <uint8_t N, typename T>
cosmodon::vector<N, T>::vector(cosmodon::vector<N, T> &&other) : vector()
{
    swap(other);
}

// Destructor.
template <uint8_t N, typename T>
cosmodon::vector<N, T>::~vector()
{
    delete [] m_values;
}

// Resets this vector.
template <uint8_t N, typename T>
void cosmodon::vector<N, T>::reset()
{
    for (uint8_t i = 0; i < N; i++) {
        m_values[i] = 0;
    }
}

// Swap this vector with another vector.
template <uint8_t N, typename T>
void cosmodon::vector<N, T>::swap(vector<N, T>& other)
{
    for (uint8_t i = 0; i < N; i++) {
        std::swap(m_values[i], other.m_values[i]);
    }
}

// Assignment to vector operator.
template <uint8_t N, typename T>
cosmodon::vector<N, T>& cosmodon::vector<N, T>::operator=(cosmodon::vector<N, T> other)
{
    swap(other);
    return *this;
}

// Assignment to matrix operator.
template <uint8_t N, typename T>
cosmodon::vector<N, T>& cosmodon::vector<N, T>::operator=(cosmodon::matrix<N, 1, T> &other)
{
    for (uint8_t i = 0; i < N; i++) {
        m_values[i] = other[i][0];
    }
    return *this;
}

// Subscript operator.
template <uint8_t N, typename T>
T& cosmodon::vector<N, T>::operator[](uint8_t index)
{
    return &m_values[index];
}

// Subscript operator with const.
template <uint8_t N, typename T>
T& cosmodon::vector<N, T>::operator[](uint8_t index) const
{
    return &m_values[index];
}

// Convert to vertical matrix.
template <uint8_t N, typename T>
cosmodon::vector<N, T>::operator cosmodon::matrix<N, 1, T>()
{
    cosmodon::matrix<N, 1, T> result;

    for (uint8_t i = 0; i < N; i++) {
        result[i][0] = m_values[i];
    }
}

// Convert to horizontal matrix.
template <uint8_t N, typename T>
cosmodon::vector<N, T>::operator cosmodon::matrix<1, N, T>()
{
    cosmodon::matrix<N, 1, T> result;

    for (uint8_t i = 0; i < N; i++) {
        result[0][i] = m_values[i];
    }
}

// Convert to string.
template <uint8_t N, typename T>
cosmodon::vector<N, T>::operator std::string()
{
    std::string result;

    result += "(";
    for (uint8_t i = 0; i < N; i++) {
        result += std::to_string(m_values[i]) + ", ";
    }

    // Remove extra comma and space.
    result.pop_back();
    result.pop_back();
    return result + ")";
}
