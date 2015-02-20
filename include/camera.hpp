#ifndef COSMODON_CAMERA_HPP
#define COSMODON_CAMERA_HPP

#include "component/position.hpp"
#include "transformation.hpp"

namespace cosmodon
{
    /**
     * A camera. Used to control the view of rendered objects.
     */
    class camera : public component::position
    {
        // Target position to look at.
        vector m_target;

        // Orientation of the camera.
        vector m_orientation;

        // Field of view of camera "lens."
        number m_fov;

        // Aspect ratio of camera "lens."
        number m_aspect;

        // Clipping values.
        number m_near;
        number m_far;

        // Current view matrix.
        matrix m_view;

        // Current projection matrix.
        matrix m_projection;

    public:
        /**
         * Constructor.
         */
        camera();

        /**
         * Updates the projection matrix.
         */
        void update_projection();

        /**
         * Updates the view matrix.
         */
        void update_view();

        /**
         * Sets field of view.
         *
         * Updates projection matrix.
         */
        void set_fov(number fov);

        /**
         * Sets aspect ratio.
         *
         * Updates projection matrix.
         */
        void set_aspect(number aspect);

        /**
         * Sets near and far clipping distances.
         *
         * Updates projection matrix.
         */
        void set_clipping(number near, number far);

        /**
         * Sets the camera orientation.
         *
         * Updates the view matrix.
         */
        void set_orientation(vector orientation);

        /**
         * Sets the camera target.
         *
         * Updates the view matrix.
         */
        void set_target(vector target);

        /**
         * Retrieves the camera target.
         */
        cosmodon::vector get_target() const;

        /**
         * Moves the camera position, relative to the current position.
         */
        using component::position::move;

        /**
         * Sets the camera position by vector.
         */
        using component::position::set_position;

        /**
         * Sets the camera position by components.
         */
        virtual void set_position(number set_x, number set_y, number set_z = 0) override;

        /**
         * Gets the camera position.
         */
        using component::position::get_position;

        /**
         * Retrieves the orientation matrix.
         */
        const matrix& get_view() const;

        /**
         * Retrieves the perspective matrix.
         */
        const matrix& get_projection() const;
    };
}

#endif
