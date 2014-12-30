#ifndef COSMODON_MATRIX_HPP
#define COSMODON_MATRIX_HPP

/**
 * Matrix declaration and definition.
 */
namespace cosmodon
{
    /**
     * A matrix of R rows and C columns, with T-type values.
     */
    template <uint8_t R, uint8_t C, typename T = float>
    class matrix
    {
    protected:
        // Internal array of matrix values.
        T *m_values;

    public:
        /**
         * Constructor.
         */
        matrix();

        /**
         * Copy constructor.
         */
        matrix(matrix<R, C, T> &other);

        /**
         * Destructor.
         */
        ~matrix();

        /**
         * Generates a matrix of zeroes.
         */
        void zero();

        /**
         * Generates an identity matrix.
         *
         * Nothing happens if the row and column counts are not equivalent.
         */
        void identity();

        /**
         * Swaps this matrix with a different matrix.
         */
        void swap(matrix<R, C, T> &other);

        /**
         * Assignment to matrix operator.
         */
        matrix<R, C, T>& operator=(matrix<R, C, T> other);

        /**
         * Subscript operator, to access matrix rows.
         *
         * Returns a reference to
         */
        T* operator[](uint8_t index);
    };
}

// Constructor.
template <uint8_t R, uint8_t C, typename T>
cosmodon::matrix<R, C, T>::matrix()
{
    m_values = new T[R * C];
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

// Swap matrix.
template <uint8_t R, uint8_t C, typename T>
void cosmodon::matrix<R, C, T>::swap(matrix<R, C, T> &other)
{
    T temp;

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

// Subscript operator.
template <uint8_t R, uint8_t C, typename T>
T* cosmodon::matrix<R, C, T>::operator[](uint8_t index)
{
    return &m_values[index*C];
}

// Addition operator.
template <uint8_t R, uint8_t C, typename T>
cosmodon::matrix<R, C, T> operator+(const cosmodon::matrix<R, C, T> &A, const cosmodon::matrix<R, C, T> &B)
{
    cosmodon::matrix<R, C, T> result;
    for (uint8_t i = 0; i < R; i++) {
        for (uint8_t j = 0; i < C; j++) {
            result[i][j] = A.m_values[i][j] + B.m_values[i][j];
        }
    }
    return result;
}

// Subtraction operator.
template <uint8_t R, uint8_t C, typename T>
cosmodon::matrix<R, C, T> operator-(const cosmodon::matrix<R, C, T> &A, const cosmodon::matrix<R, C, T> &B)
{
    cosmodon::matrix<R, C, T> result;
    for (uint8_t i = 0; i < R; i++) {
        for (uint8_t j = 0; j < C; j++) {
            result.m_values[i][j] = A.m_values[i][j] - B.m_values[i][j];
        }
    }
    return result;
}

// Multiplication operator.
template <uint8_t R, uint8_t N, uint8_t C, typename T>
cosmodon::matrix<R, C, T> operator*(const cosmodon::matrix<R, N, T> &A, const cosmodon::matrix<N, C, T> &B)
{
    cosmodon::matrix<R, C, T> result;
    T sum;

    for (uint8_t i = 0; i < R; i++) {
        for (uint8_t j = 0; j < C; j++) {
            sum = 0;
            for (uint8_t k = 0; k < N; k++) {
                sum += A.m_values[i][k] * B.m_values[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

#endif
