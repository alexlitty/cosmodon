#ifndef COSMODON_LAYER
#define COSMODON_LAYER

#include <vector>
#include <irrlicht/irrlicht.h>

namespace cosmodon
{
        namespace layer
        {
            /**
             * A base and empty execution layer.
             *
             * These should be used to separate different states of a system -- not to layer graphics
             * or other components.
             *
             * Derive and define virtual functions to implement a layer.
             */
            class base
            {
            protected:
                irr::video::IVideoDriver* m_driver;
                irr::scene::ISceneManager* m_scene_manager;

                // Reference to this application's network context.
                void *m_context;

                // Children layers.
                std::vector<base*> m_children;

                // Root scene node, for ease of access.
                irr::scene::ISceneNode* m_scene_root;
    
            public:
                /**
                 * Constructor.
                 */
                base(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *scene_manager, void *context);

                /**
                 * Perform a tick on this layer.
                 *
                 * Upon returning false, the layer should be removed. Not another tick will pass.
                 */
                virtual bool tick() = 0;

                /**
                 * Set the network context.
                 */
                void set_context(void *context);
            };
        }
    
}

#endif
