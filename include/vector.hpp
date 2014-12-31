#ifndef COSMODON_VECTOR_HPP
#define COSMODON_VECTOR_HPP

#include "matrix.hpp"

namespace cosmodon
{
    /**
     * A vector of N values with type T.
     *
     * Identifies a point in space, depicts a magnitude with direction, and more. Not to be
     * confused with std::vector, a storage class.
     */
    template <uint8_t N, typename T = float>
    class vector
    {
    protected:
        // Internal array of vector values.
        T *m_values;

    public:
        /**
         * Constructor.
         */
        vector();

        /**
         * Copy constructor.
         */
        vector(vector<N, T> &other);

        /**
         * Move constructor.
         */
        vector(vector<N, T> &&other);

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
        void swap(vector<N, T> &other);

        /**
         * Assignment to vector operator.
         */
        vector<N, T>& operator=(vector<N, T> other);

        /**
         * Assignment to matrix operator.
         */
        vector<N, T>& operator=(matrix<N, 1, T> &other);

        /**
         * Subscript operator.
         */
        T& operator[](uint8_t index);

        /**
         * Subscript operator with const.
         */
        T& operator[](uint8_t index) const;

        /**
         * Convert to vertical matrix.
         */
        operator cosmodon::matrix<N, 1, T>();

        /**
         * Convert to horizontal matrix.
         */
        operator cosmodon::matrix<1, N, T>();

        /**
         * Convert to string.
         */
        operator std::string();
    };
}

// Include member definitions.
#include "vector.tpp"

// Equivalency operator.
template <uint8_t M, uint8_t N, typename T, typename U>
bool operator==(const cosmodon::vector<M, T> &lhs, const cosmodon::vector<N, U> &rhs)
{
    // Size.
    if (M != N) {
        return false;
    }

    // Values.
    for (uint8_t i = 0; i < N; i++) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

// Inequivalency operator.
template <uint8_t M, uint8_t N, typename T, typename U>
bool operator!=(const cosmodon::vector<M, T> &lhs, const cosmodon::vector<N, U> &rhs)
{
    return !(lhs == rhs);
}

// Addition operator.
template <uint8_t N, typename T>
cosmodon::vector<N, T> operator+(const cosmodon::vector<N, T> &lhs, const cosmodon::vector<N, T> &rhs)
{
    cosmodon::vector<N, T> result;
    for (uint8_t i = 0; i < N; i++) {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

// Subtraction operator.
template <uint8_t N, typename T>
cosmodon::vector<N, T> operator-(const cosmodon::vector<N, T> &lhs, const cosmodon::vector<N, T> &rhs)
{
    cosmodon::vector<N, T> result;
    for (uint8_t i = 0; i < N; i++) {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}

// Output stream operator.
template <uint8_t N, typename T>
std::ostream& operator<<(std::ostream &stream, cosmodon::vector<N, T> &value)
{
    stream << static_cast<std::string>(value);
    return stream;
}

#endif
