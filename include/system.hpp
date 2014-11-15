#ifndef COSMODON_SYSTEM
#define COSMODON_SYSTEM

#include "irrlicht/irrlicht.h"
#include "zmq/zmq.h"
#include "layer.hpp"
#include "exception.hpp"
#include "network_utility.hpp"

namespace cosmodon
{
    /**
     * The Central Operation Class of Cosmodon Applications.
     *
     * May throw cosmo::exception classes.
     */
    class system
    {
    protected:
        // 0MQ Context.
        void *m_network_context;

        // Irrlicht variables.
        irr::IrrlichtDevice* m_irrlicht;
        irr::video::IVideoDriver* m_driver;
        irr::scene::ISceneManager* m_scene_manager;

        // Root execution layer.
        layer::base* m_layer_root;

    public:
        // Constructor.
        system(irr::IrrlichtDevice *irrlicht, layer::base *layer_root);

        // Destructor.
        ~system();

        // Pass execution to the system. Program will not leave this function until end.
        void execute();
    };
}

#endif
