#ifndef COSMODON_MATRIX_HPP
#define COSMODON_MATRIX_HPP

#include <string>

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
         * Move constructor.
         */
        matrix(matrix<R, C, T> &&other);

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
         * Assignment to scalar operator.
         */
        matrix<R, C, T>& operator=(T other);

        /**
         * Subscript operator, to access matrix rows.
         *
         * Use another subscript to access matrix values.
         */
        T* operator[](uint8_t index);

        /**
         * Subscript operator with const, to read matrix rows.
         *
         * Use another subscript to access matrix values.
         */
        T* operator[](uint8_t index) const;

        /**
         * Converts matrix to a string.
         *
         * Excellent for debugging.
         */
        operator std::string();
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

// Equivalency operator.
template <uint8_t R, uint8_t C, uint8_t M, uint8_t N, typename T, typename U>
bool operator==(cosmodon::matrix<R, C, T> &lhs, cosmodon::matrix<M, N, U> &rhs)
{
    // Check matrix sizes.
    if (R != M || C != N) {
        return false;
    }

    // Check each member.
    for (uint8_t i = 0; i < R; i++) {
        for (uint8_t j = 0; j < C; j++) {
            if (lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Inequivalency operator.
template <uint8_t R, uint8_t C, uint8_t M, uint8_t N, typename T, typename U>
bool operator!=(cosmodon::matrix<R, C, T> &lhs, cosmodon::matrix<M, N, U> &rhs)
{
    return !(lhs == rhs);
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

// Addition operator.
template <uint8_t R, uint8_t C, typename T>
cosmodon::matrix<R, C, T> operator+(const cosmodon::matrix<R, C, T> &A, const cosmodon::matrix<R, C, T> &B)
{
    cosmodon::matrix<R, C, T> result;
    for (uint8_t i = 0; i < R; i++) {
        for (uint8_t j = 0; j < C; j++) {
            result[i][j] = A[i][j] + B[i][j];
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
            result[i][j] = A[i][j] - B[i][j];
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
                sum += A[i][k] * B[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

// Output stream operator.
template <uint8_t R, uint8_t C, typename T>
std::ostream& operator<<(std::ostream &stream, cosmodon::matrix<R, C, T> &other)
{
    stream << static_cast<std::string>(other);
    return stream;
}

#endif
