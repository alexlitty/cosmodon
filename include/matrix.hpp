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
         * Default constructor.
         */
        matrix();

        /**
         * Constructor.
         */
        matrix(
            number x0, number x1, number x2, number x3,
            number y0, number y1, number y2, number y3,
            number z0, number z1, number z2, number z3,
            number w0, number w1, number w2, number w3
        );

        /**
         * Copy constructor.
         */
        matrix(const matrix &other);

        /**
         * Move constructor.
         */
        matrix(matrix &&other);

        /**
         * Destructor.
         */
        virtual ~matrix();

        /**
         * Sets matrix values.
         */
        void set(
            number x0, number x1, number x2, number x3,
            number y0, number y1, number y2, number y3,
            number z0, number z1, number z2, number z3,
            number w0, number w1, number w2, number w3
        );

        /**
         * Retrieve raw matrix values as an array.
         */
        const number* raw() const;

        /**
         * Generates a matrix of zeroes.
         */
        void set_zero();

        /**
         * Generates an identity matrix.
         */
        void set_identity();

        /**
         * Generate a translation matrix.
         */
        void set_translation(number x, number y, number z = 0);

        /**
         * Generate a scale matrix.
         */
        void set_scale(number x, number y, number z = 1);

        /**
         * Generate a rotation matrix about the x-axis.
         */
        void set_rotation_x(number radians);

        /**
         * Generate a rotation matrix about the y-axis.
         */
        void set_rotation_y(number radians);

        /**
         * Generate a rotation matrix about the z-axis.
         */
        void set_rotation_z(number radians);

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
        operator std::string() const;
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
std::ostream& operator<<(std::ostream &stream, const cosmodon::matrix &value);

#endif
