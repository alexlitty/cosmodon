#ifndef COSMODON_COMPONENT_POSITION
#define COSMODON_COMPONENT_POSITION

#include "../vector.hpp"

namespace cosmodon
{
    namespace component
    {
        /**
         * Positioned component.
         *
         * Children are subject to positioning.
         */
        class position : public vector
        {
        public:
            /**
             * Moves this object relative to its current position.
             */
            void move(number move_x, number move_y, number move_z = 0);

            /**
             * Sets object position.
             */
            virtual void set_position(number set_x, number set_y, number set_z = 0);

            /**
             * Gets object position.
             */
            virtual vector get_position() const;
        };
    }
}

#endif
