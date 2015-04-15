#ifndef COSMODON_VERTEX
#define COSMODON_VERTEX

#include <vector>
#include <string>
#include <ostream>

#include "color.hpp"
#include "../draw/canvas.hpp"
#include "primitive.hpp"
#include "vector.hpp"

namespace cosmodon
{
    /**
     * A vertex.
     *
     * Functionally identical to a point, but separated to add functionality.
     *
     * @@@ Implement graphic component.
     */
    class vertex : public vector, public color
    {
    public:
        // w component.
        cosmodon::number w;

        /**
         * Default constructor.
         */
        vertex();

        /**
         * Constructor, without w component.
         */
        vertex(number init_x, number init_y, number init_z, cosmodon::color c = cosmodon::black);

        /**
         * Constructor, with w component.
         */
        vertex(number init_x, number init_y, number init_z, number init_w,
          cosmodon::color c = cosmodon::black
        );

        /**
         * Constructor, from vector.
         */
        vertex(const vector &other, cosmodon::color c = cosmodon::black);

        /**
         * Copy constructor.
         */
        vertex(const vertex &copy);

        /**
         * Assignment to color operator.
         */
        cosmodon::vertex& operator=(const color value);

        /**
         * Convert to string, to visually explain its internal coordinates.
         */
        operator std::string() const;
    };
}

// Vertex and matrix multiplication.
cosmodon::vertex operator*(const cosmodon::matrix &lhs, const cosmodon::vertex &rhs);
cosmodon::vertex operator*(const cosmodon::vertex &lhs, const cosmodon::matrix &rhs);

#endif
