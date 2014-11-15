#ifndef COSMODON_COMPONENT
#define COSMODON_COMPONENT

#include <irrlicht/irrlicht.h>

namespace cosmodon
{
    namespace component
    {
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
         * Used by the System to communicate between clients and servers. The System collects
         * information gathered by this component, and pushes information into it.
         */
        class network
        {
                
        };
    }
}

#endif
