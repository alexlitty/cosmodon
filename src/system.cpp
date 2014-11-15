#include <system.hpp>

using namespace cosmodon;

// System constructor.
system::system(irr::IrrlichtDevice* irrlicht, layer::base* layer_root)
{
    // Prepare 0MQ.
    m_network_context = zmq_ctx_new();
    if (m_network_context == nullptr) {
        throw exception::fatal(network::error());
    }
    layer_root->set_context(m_network_context);

    // Prepare irrlicht.
    m_irrlicht = irrlicht;
    m_driver = irrlicht->getVideoDriver();
    m_scene_manager = irrlicht->getSceneManager();
    m_layer_root = layer_root;

    // Disable output.
    irrlicht->getLogger()->setLogLevel(irr::ELL_ERROR);
}

// System destructor.
system::~system()
{
    delete m_irrlicht;
}

// Pass execution to system.
void system::execute()
{
    while (m_irrlicht->run()) {
        m_layer_root->tick();

        // Draw.
        m_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
        m_scene_manager->drawAll();
        m_driver->endScene();
    }
}
