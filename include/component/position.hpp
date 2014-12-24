#ifndef COSMODON_COMPONENT_POSITION
#define COSMODON_COMPONENT_POSITION

#include "../point.hpp"

namespace cosmodon
{
    namespace component
    {
        /**
         * Positioned component.
         *
         * Children are subject to positioning.
         */
        class position
        {
        protected:
            // Internal position.
            cosmodon::point m_position;

        public:
            // @@@ Positioning functions
        };
    }
}

#endif
