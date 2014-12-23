#ifndef COSMODON_COMPONENT
#define COSMODON_COMPONENT

#include "buffer.hpp"

namespace cosmodon
{
    namespace component
    {
        /**
         * Programmable component.
         *
         * Used to give an object executable purpose.
         */
        class code
        {
        public:
            /**
             * Execute this object's program.
             *
             * Implemented by derived class.
             *
             * Returns true if the program requires further execution, or false if the program
             * is finished.
             */
            virtual bool execute() = 0;
        };

        /**
         * Physical component.
         *
         * Provides child objects with customizable physics features.
         */
        class physics
        {

        };

        /**
         * Graphical component.
         *
         * Allows child objects to be rendered. Subject to physics, which may be individually
         * disabled.
         */
        class graphic : public physics
        {

        };

        /**
         * Audio component, indicating an object makes sound.
         *
         * Used to emit all sounds: sound effects, music and otherwise.
         */
        class audio
        {

        };

        /**
         * Control component, indicating an object may be controlled by the user.
         *
         * All controls are handled through an object with this component.
         */
        class control
        {

        };

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
