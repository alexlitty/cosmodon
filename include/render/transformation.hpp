#ifndef COSMODON_TRANSFORMATION_HPP
#define COSMODON_TRANSFORMATION_HPP

#include "component/position.hpp"
#include "matrix.hpp"

namespace cosmodon
{
    /**
     * A class to describe and group vertex transformations.
     *
     * Contains a translation, scale, and rotation matrix. Produces a combination matrix.
     */
    class transformation : public component::position
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
         * Sets the absolute scale.
         */
        void set_scale(number x, number y, number z = 1);

        /**
         * Sets the absolute scale of all components.
         */
        void set_scale(number s);

        /**
         * Perform a relative translation.
         *
         * An alias for move().
         */
        void translate(number v_x, number v_y, number v_z = 0);

        /**
         * Perform a relative translation.
         *
         * Calls set_position() with new final coordinates.
         */
        using component::position::move;

        /**
         * Perform an absolute translation.
         */
        virtual void set_position(number value_x, number value_y, number value_z) override;

        /**
         * Perform a rotation.
         */
        void rotate(number x, number y = 0, number z = 0);

        /**
         * Returns the resulting transformation matrix.
         */
        const matrix& get_matrix() const;

        /**
         * Convert to matrix, outputting the result matrix.
         */
        operator matrix();
    };

    /**
     * Default transformation.
     */
    extern transformation no_transformation;
}

#endif
