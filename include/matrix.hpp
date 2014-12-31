#ifndef COSMODON_MATRIX_HPP
#define COSMODON_MATRIX_HPP

#include <string>
#include "math.hpp"

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
        virtual ~matrix();

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
         * Perform a translation on 4x4 matrices.
         *
         * If the matrix is not 4x4, nothing happens.
         */
        void translate(T x, T y, T z = 0);

        /**
         * Perform a scaling on 4x4 matrices.
         *
         * If the matrix is not 4x4, nothing happens.
         */
        void scale(T x, T y, T z = 1);

        /**
         * Generate a 4x4 rotation matrix, using a rotation about the x-axis.
         */
        void rotate_x(T radians);

        /**
         * Generate a 4x4 rotation matrix, using a rotation about the x-axis.
         */
        void rotate_y(T radians);

        /**
         * Generate a 4x4 rotation matrix, using a rotation about the x-axis.
         */
        void rotate_z(T radians);

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

// Equivalency operator.
template <uint8_t R, uint8_t C, uint8_t M, uint8_t N, typename T, typename U>
bool operator==(cosmodon::matrix<R, C, T> &lhs, cosmodon::matrix<M, N, U> &rhs)
{
    // Size.
    if (R != M || C != N) {
        return false;
    }

    // Values.
    for (uint8_t i = 0; i < R; i++) {
        for (uint8_t j = 0; j < C; j++) {
            if (lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Include member definitions.
#include "matrix.tpp"

// Inequivalency operator.
template <uint8_t R, uint8_t C, uint8_t M, uint8_t N, typename T, typename U>
bool operator!=(cosmodon::matrix<R, C, T> &lhs, cosmodon::matrix<M, N, U> &rhs)
{
    return !(lhs == rhs);
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
std::ostream& operator<<(std::ostream &stream, cosmodon::matrix<R, C, T> &value)
{
    stream << static_cast<std::string>(value);
    return stream;
}

#endif
