#ifndef COSMODON_PHYSICS_PHYSICAL_HPP
#define COSMODON_PHYSICS_PHYSICAL_HPP

#include "../render/model.hpp"
#include "boundary.hpp"

namespace cosmodon
{
    /**
     * Base class for all physics-obeying objects.
     *
     * Alone, this class explains the physical properties of an object: The ball has a constant velocity, the pencil is at rest with a vertical acceleration.
     *
     * Children classes choose how to use this information when time passes: All the vertices in a solid move together, while gas vertices are free to separate. You can customize how vertices react to physics by implementing your own classes.
     *
     * This class is not meant to directly interact with another physical object. If you want two objects to interact, an external method -- like physics::system -- should analyze and change the properties of your objects.
     */
    class physical : public model
    {
    protected:
        // Current velocity in m/s.
        vector m_velocity;

        // Current acceleration in m/s*s.
        vector m_acceleration;

        // Whether the object is static and unable to move.
        bool m_static;

        // Boundary model, which summarizes the physical shape.
        boundary *m_boundary;

    public:
        /**
         * Constructor.
         *
         * Initializes all vectors to 0.
         */
        physical();

        /**
         * Sets velocity.
         */
        void set_velocity(vector velocity);

        /**
         * Retrieves velocity.
         */
        vector get_velocity() const;

        /**
         * Sets acceleration.
         */
        void set_acceleration(vector acceleration);

        /**
         * Retrieves acceleration.
         */
        vector get_acceleration() const;

        /**
         * Determines if an intersection exists between this object and another object, using boundaries if available.
         *
         * @param other Object to compare against.
         *
         * @returns True if an intersection exists, or false otherwise.
         */
        virtual bool intersects(const physical &other) const;

        /**
         * Sets the static status.
         *
         * A static object is unable to move, but influences other objects. Velocity and acceleration are set to zero.
         */
        void set_static(bool s);

        /**
         * Retrieves the static status.
         *
         * A static object has no acceleration and no velocity, but influences other objects.
         */
        bool is_static() const;
    };
}

#endif
