#include <system.hpp>

using namespace cosmodon;

// System constructor.
system::system(irr::IrrlichtDevice* irrlicht, layer::base* root)
{
    // Prepare 0MQ.
    m_network_context = zmq_ctx_new();
    if (m_network_context == nullptr) {
        throw exception::fatal(network::error());
    }

    // Prepare irrlicht.
    m_irrlicht = irrlicht;
    if (irrlicht != nullptr) {
        m_driver = irrlicht->getVideoDriver();
        m_scene_manager = irrlicht->getSceneManager();
    }

    // Prepare root layer.
    set_layer(root);

    // Disable irrlicht output.
    irrlicht->getLogger()->setLogLevel(irr::ELL_ERROR);
}

// System destructor.
system::~system()
{
    delete m_irrlicht;
    delete m_layer;
}

// Pass execution to system.
void system::execute()
{
    while (m_layer != nullptr) {
        if (!m_layer->tick()) {
            delete m_layer;
            m_layer = nullptr;
            return;
        }

        // Draw if applicable.
        if (m_irrlicht != nullptr && m_irrlicht->run()) {
            m_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
            m_scene_manager->drawAll();
            m_driver->endScene();
        }
    }
}

// Generate and return system settings.
settings system::get_settings()
{
    settings ret;
    ret.irrlicht = m_irrlicht;
    ret.network_context = m_network_context;
    return ret;
}

// Set the layer root, returning the old root.
layer::base *system::set_layer(layer::base *root)
{
    layer::base *old_layer = m_layer;
    m_layer = root;

    // Pass system settings to layer.
    if (m_layer != nullptr) {
        m_layer->set_settings(get_settings());
    }

    // Return old layer.
    return old_layer;
}
