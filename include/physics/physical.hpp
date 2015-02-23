#ifndef COSMODON_PHYSICS_PHYSICAL_HPP
#define COSMODON_PHYSICS_PHYSICAL_HPP

#include "../model.hpp"

namespace cosmodon
{
    /**
     * Base class for all physics-obeying objects.
     */
    class physical : public model
    {
    protected:
        // Current velocity in m/s.
        vector m_velocity;

        // Current acceleration in m/s*s.
        vector m_acceleration;

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
         * Perform physics on this object.
         */
        virtual void pass_time(number seconds) = 0;
    };
}

#endif
