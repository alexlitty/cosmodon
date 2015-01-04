#ifndef COSMODON_CAMERA_HPP
#define COSMODON_CAMERA_HPP

#include "component/position.hpp"
#include "transformation.hpp"

namespace cosmodon
{
    /**
     * A camera. Used to control the view of rendered objects.
     *
     * Explained with a transformation view, and a perspective matrix.
     */
    class camera : protected component::position
    {
        // Target position to look at.
        vector m_target;

        // Up vector for the camera.
        vector m_up;

        // The orientation of the camera.
        matrix m_orientation;

        // The perspective of the camera.
        matrix m_perspective;

        /**
         * Updates the view matrix.
         */
        void update_view();

    public:
        /**
         * Moves the camera position, relative to the current position.
         */
        using component::position::move;

        /**
         * Sets the camera position.
         */
        virtual void set_position(number set_x, number set_y, number set_z = 0) override;

        /**
         * Gets the camera position.
         */
        using component::position::get_position;

        /**
         * Sets the point where the camera should look.
         */
        void set_orientation(vector target, vector up);

        /**
         * Sets the perspective of the camera.
         */

        /**
         * Retrieves the orientation matrix.
         */
        const matrix& get_orientation() const;

        /**
         * Retrieves the perspective matrix.
         */
        const matrix& get_perspective() const;
    };
}

#endif
