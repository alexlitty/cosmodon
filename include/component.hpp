#ifndef COSMODON_COMPONENT
#define COSMODON_COMPONENT

#include "irrlicht/irrlicht.h"
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
         * Three-Dimmensional Graphical or Physical component, closely integrated with the
         * Irrlicht Scene Environment.
         *
         * May obey physics. May be invisible.
         *
         * The core model component is not derived from any class. When implemented, the child
         * should also inherit from any type of Irrlicht Scene Node.
         */
        class model : public irr::scene::ISceneNode
        {
        protected:
            // Boundary storage.
            irr::core::aabbox3d<irr::f32> m_bounding_box;
        
        public:
            /**
             * Constructor.
            */
            model(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id);

            /**
             * Return the model boundaries, implementing the virtual ISceneNode method.
             */
            const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
        };

        /**
         * Two-Dimmensional Graphical component. Not closely integrated with any particular
         * Irrlicht functionality; This is up to class children to implement.
         *
         * Used to display part of a GUI, or other "flat" graphics.
         */
        class graphic
        {
        public:
            // Draws the graphic element.
            virtual void draw(irr::video::IVideoDriver* driver) = 0;
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
             * Returns true if successful, false otherwise.
             */
            virtual bool network_serialize(cosmodon::buffer &buffer) = 0;

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
