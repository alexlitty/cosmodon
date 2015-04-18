#ifndef COSMODON_RENDER_GENERATE_HPP
#define COSMODON_RENDER_GENERATE_HPP

#include "vertex.hpp"

namespace cosmodon
{
    /**
     * A collection of shape generation methods, appended to the vertices parameter.
     */
    namespace generate
    {
        /**
         * Generates an equilateral triangle.
         *
         * @todo  Not actually equilateral.
         *
         * @param  v       Vertices collection to append.
         * @param  radius  Distance from the center to all points.
         */
        void triangle(vertices &v, number radius);

        /**
         * Generates a square.
         */
        void square(vertices &v, number radius);

        /**
         * Generates a rectangle.
         */
        void rectangle(vertices &v, number width, number height);

        /**
         * Generates a box.
         */
        void cuboid(vertices &v, number radius);

        /**
         * Generates a pyramid.
         */
        void pyramid(vertices &v, number width, number height);
    }
}

#endif
