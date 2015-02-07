#ifndef COSMODON_VECTOR_HPP
#define COSMODON_VECTOR_HPP

#include <iostream>
#include "matrix.hpp"

namespace cosmodon
{
    /**
     * A vector of 3 components. Not a container, like std::vector.
     *
     * Identifies a point in space, depicts a magnitude with direction, and more.
     */
    class vector
    {
    public:
        // Vector components.
        number x;
        number y;
        number z;

        /**
         * Constructor.
         */
        vector(number init_x = 0, number init_y = 0, number init_z = 0);

        /**
         * Copy constructor.
         */
        vector(vector &other);

        /**
         * Move constructor.
         */
        vector(vector &&other);

        /**
         * Destructor.
         */
        ~vector();

        /**
         * Resets this vector, setting all components to zero.
         */
        void reset();

        /**
         * Swap this vector with another vector.
         */
        void swap(vector &other);

        /**
         * Calculates vector magnitude.
         */
        number magnitude() const;

        /**
         * Returns a normalized version of this vector.
         */
        vector normalize() const;

        /**
         * Assignment to vector operator.
         */
        vector& operator=(vector other);

        /**
         * Convert to string.
         */
        operator std::string();
    };
}

// Equivalency operator.
bool operator==(const cosmodon::vector &lhs, const cosmodon::vector &rhs);

// Inequivalency operator.
bool operator!=(const cosmodon::vector &lhs, const cosmodon::vector &rhs);

// Addition operator.
cosmodon::vector operator+(const cosmodon::vector &lhs, const cosmodon::vector &rhs);

// Subtraction operator.
cosmodon::vector operator-(const cosmodon::vector &lhs, const cosmodon::vector &rhs);

// Multiply a vector by a matrix.
cosmodon::vector operator*(const cosmodon::matrix &lhs, const cosmodon::vector &rhs);
cosmodon::vector operator*(const cosmodon::vector &lhs, const cosmodon::matrix &rhs);

// Multiply vectors by performing a cross-product.
cosmodon::vector operator*(const cosmodon::vector &lhs, const cosmodon::vector &rhs);

// Output stream operator.
std::ostream& operator<<(std::ostream &stream, cosmodon::vector &value);

#endif
