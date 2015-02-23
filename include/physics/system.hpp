#ifndef COSMODON_PHYSICS_SYSTEM_HPP
#define COSMODON_PHYSICS_SYSTEM_HPP

#include <vector>
#include "physical.hpp"

namespace cosmodon
{
    namespace physics
    {
        /**
         * A standard physics system, where physical objects interact under the passage of time.
         *
         * @@@ Replace with custom set.
         */
        class system : public physical
        {
        protected:
            // Collection of normal objects.
            std::vector<physical*> m_objects;

        public:
            /**
             * Adds an object to this system.
             */
            void add(physical &object);

            /**
             * Checks if an object is in the system.
             */
            bool is_inside(physical &object) const;

            /**
             * Removes an object from this system.
             */
            void remove(physical &object);

            /**
             * Perform physics.
             */
            virtual void pass_time(number seconds);
        };
    }
}

#endif
