#ifndef COSMODON_COMPONENT_NETWORK
#define COSMODON_COMPONENT_NETWORK

#include "../buffer.hpp"

namespace cosmodon
{
    namespace component
    {
        /**
         * Network component.
         *
         * Derived classes intend to send or receive network data.
         */
        class network
        {
        public:
            /**
             * Serialize this object into a network buffer, to be reproduced elsewhere.
             *
             * The philosophy of Cosmodon suggests this method never fails. An object which has an
             * unserializable state should never be asked to serialize itself.
             */
            virtual void network_serialize(cosmodon::buffer &buffer) = 0;

            /**
             * Deserialize a network buffer to reproduce this object.
             *
             * Returns true if successful, false otherwise.
             */
            virtual bool network_deserialize(cosmodon::buffer &buffer) = 0;
        };
    }
}

#endif
