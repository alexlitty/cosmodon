#include <engine.hpp>

using namespace cosmodon;

// Engine constructor.
engine::engine(layer::base *root)
{
    m_irrlicht = nullptr;
    m_net = new network::context;
    set_layer(root);
}

engine::engine(bool graphics, layer::base *root)
{
    // Initialize irrlicht.
    m_irrlicht = irr::createDevice(
        graphics ? irr::video::EDT_SOFTWARE : irr::video::EDT_NULL,
        irr::core::dimension2d<irr::u32>(640, 480),
        16, false, false, false, nullptr
    );

    // Check irrlicht.
    if (!m_irrlicht) {
        throw exception::fatal("Failed to Initialize Irrlicht");
    }

    // Prepare irrlicht variables.
    m_driver = m_irrlicht->getVideoDriver();
    m_scene_manager = m_irrlicht->getSceneManager();

    // Disable irrlicht output.
    m_irrlicht->getLogger()->setLogLevel(irr::ELL_ERROR);

    // Set layer and network context.
    m_net = new network::context;
    set_layer(root);
}

// System destructor.
engine::~engine()
{
    delete m_irrlicht;
    delete m_layer;
}

// Pass execution to system.
void engine::execute()
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
settings engine::get_settings()
{
    settings ret;
    ret.irrlicht = m_irrlicht;
    ret.network_context = m_net;
    return ret;
}

// Set the layer root, returning the old root.
layer::base* engine::set_layer(layer::base *root)
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
