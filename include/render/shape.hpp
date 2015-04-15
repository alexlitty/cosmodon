#ifndef COSMODON_SHAPE_HPP
#define COSMODON_SHAPE_HPP

#include "vertex.hpp"

namespace cosmodon
{
    /**
     * A collection of shape generation methods, appended to the vertices parameter.
     */
    namespace shape
    {
        /**
         * Generates an equilateral triangle.
         */
        void triangle(vertices &v, number length);

        /**
         * Generates a square.
         */
        void square(vertices &v, number length, vector center, vector point);

        /**
         * Generates a rectangle.
         */
        void rectangle(vertices &v, number width, number height);

        /**
         * Generates a pyramid.
         */
        void pyramid(vertices &v, number width, number height);
    }
}

#endif
