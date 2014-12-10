#ifndef COSMODON_ENGINE
#define COSMODON_ENGINE

#include "irrlicht/irrlicht.h"
#include "layer.hpp"
#include "exception.hpp"
#include "network_utility.hpp"

namespace cosmodon
{
    /**
     * The Central Class of Cosmodon Applications.
     *
     * 
     */
    class engine
    {
    protected:
        // Irrlicht variables, for easy programming reference.
        irr::IrrlichtDevice *m_irrlicht;
        irr::video::IVideoDriver *m_driver;
        irr::scene::ISceneManager *m_scene_manager;

        // Root execution layer.
        layer::base *m_layer;

    public:
        /**
         * Constructor which does not initialize irrlicht.
         */
        engine(layer::base *layer_root = nullptr);

        /**
         * Constructor which initializes irrlicht.
         */
        engine(bool graphics, layer::base *layer_root = nullptr);

        /**
         * Destructor.
         */
        ~engine();

        /**
         * Pass execution to the engine.
         *
         * Finishes when a tick on the root layer returns false.
         */
        void execute();

        /**
         * Retrieve system settings.
         *
         * An instance of the settings class is generated on-the-spot.
         */
        settings get_settings();

        /**
         * Sets the root layer, returning the old root.
         */
        layer::base *set_layer(layer::base *root);
    };
}

#endif
