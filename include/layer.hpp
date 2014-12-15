#ifndef COSMODON_LAYER
#define COSMODON_LAYER

#include <vector>
#include "irrlicht/irrlicht.h"
#include "settings.hpp"

namespace cosmodon
{
    namespace layer
    {
        /**
         * A base and empty execution layer.
         *
         * Although a whole program can run in a single layer, layers intend to separate bigger
         * programs into tinier, controllable pieces of code.
         *
         * Derive and define virtual functions to implement a layer.
         */
        class base
        {
        protected:
            irr::IrrlichtDevice *m_irrlicht;
            irr::video::IVideoDriver *m_driver;
            irr::scene::ISceneManager *m_scene_manager;
            irr::scene::ISceneNode *m_scene_root;

            // Children layers.
            std::vector<base*> m_children;

        public:
            /**
             * Constructor.
             */
            base(settings s = settings(nullptr));

            /**
             * Destructor.
             */
            virtual ~base();

            /**
             * Perform a tick on this layer.
             *
             * Upon returning false, the layer should be removed. Not another tick will pass.
             */
            virtual bool tick() = 0;

            /**
             * Set layer settings.
             */
            void set_settings(settings s);
        };
    }

    /**
     * Type definition for an execution layer.
     */
    typedef layer::base layer_t;
}

#endif
