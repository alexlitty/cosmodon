#ifndef COSMODON_TRANSFORMATION_HPP
#define COSMODON_TRANSFORMATION_HPP

#include "matrix.hpp"

namespace cosmodon
{
    /**
     * A class to describe and group vertex transformations.
     *
     * Contains a translation, scale, and rotation matrix. Produces a combination matrix.
     */
    class transformation
    {
    protected:
        // Scale matrix.
        matrix m_scale;

        // Translation matrix.
        matrix m_translation;

        // Rotation matrix, about the x-axis.
        matrix m_rotation_x;

        // Rotation matrix, about the y-axis.
        matrix m_rotation_y;

        // Rotation matrix, about the z-axis.
        matrix m_rotation_z;

        // Resulting transformation matrix.
        matrix m_result;

        /**
         * Updates result matrix.
         */
        void update();

    public:
        /**
         * Perform a scaling.
         */
        void scale(number x, number y, number z = 1);

        /**
         * Perform a translation.
         */
        void translate(number x, number y, number z = 0);

        /**
         * Perform a rotation.
         */
        void rotate(number x, number y = 0, number z = 0);

        /**
         * Returns the resulting transformation matrix.
         */
        matrix& get_matrix();

        /**
         * Convert to matrix, outputting the result matrix.
         */
        operator matrix();
    };
}

#endif
