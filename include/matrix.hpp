#ifndef COSMODON_MATRIX_HPP
#define COSMODON_MATRIX_HPP

#include <string>
#include "math.hpp"
#include "number.hpp"

namespace cosmodon
{
    /**
     * A 4x4 matrix for rendering transformations.
     */
    class matrix
    {
    protected:
        // Internal array of matrix values.
        number *m_values;

    public:
        /**
         * Constructor.
         */
        matrix();

        /**
         * Copy constructor.
         */
        matrix(matrix &other);

        /**
         * Move constructor.
         */
        matrix(matrix &&other);

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
         */
        void identity();

        /**
         * Generate a translation matrix.
         */
        void translate(number x, number y, number z = 0);

        /**
         * Generate a scale matrix.
         */
        void scale(number x, number y, number z = 1);

        /**
         * Generate a rotation matrix about the x-axis.
         */
        void rotate_x(number radians);

        /**
         * Generate a rotation matrix about the y-axis.
         */
        void rotate_y(number radians);

        /**
         * Generate a rotation matrix about the z-axis.
         */
        void rotate_z(number radians);

        /**
         * Swaps this matrix with a different matrix.
         */
        void swap(matrix &other);

        /**
         * Assignmentment from matrix.
         */
        matrix& operator=(matrix other);

        /**
         * Assignmentment from scalar.
         */
        matrix& operator=(number other);

        /**
         * Subscript operator, to access matrix rows.
         *
         * Proceed with another subscript to access matrix values.
         */
        number* operator[](uint8_t index);
        number* operator[](uint8_t index) const;

        /**
         * Converts matrix to a string.
         *
         * Excellent for debugging.
         */
        operator std::string();
    };
}

// Equivalency operator.
bool operator==(cosmodon::matrix &lhs, cosmodon::matrix &rhs);

// Inequivalency operator.
bool operator!=(cosmodon::matrix &lhs, cosmodon::matrix &rhs);

// Addition operator.
cosmodon::matrix operator+(const cosmodon::matrix &A, const cosmodon::matrix &B);

// Subtraction operator.
cosmodon::matrix operator-(const cosmodon::matrix &A, const cosmodon::matrix &B);

// Multiplication operator.
cosmodon::matrix operator*(const cosmodon::matrix &A, const cosmodon::matrix &B);

// Output stream operator.
std::ostream& operator<<(std::ostream &stream, cosmodon::matrix &value);

#endif
