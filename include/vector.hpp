#ifndef COSMODON_VECTOR_HPP
#define COSMODON_VECTOR_HPP

#include "matrix.hpp"

namespace cosmodon
{
    /**
     * A vector of 3 values with type T.
     *
     * Identifies a point in space, depicts a magnitude with direction, and more. Not to be
     * confused with std::vector.
     */
    class vector
    {
    public:
        // Vector components.
        number x;
        number y;
        number z;
        number w;

        /**
         * Constructor.
         */
        vector(number init_x = 0, number init_y = 0, number init_z = 0, number init_w = 0);

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

// Output stream operator.
std::ostream& operator<<(std::ostream &stream, cosmodon::vector &value);

#endif
