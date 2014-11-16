#include <system.hpp>

using namespace cosmodon;

// System constructor.
system::system(layer::base *root)
{
    m_irrlicht = nullptr;
    m_network_context = network::initialize();
    set_layer(root);
}

system::system(bool graphics, layer::base *root)
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
    m_network_context = network::initialize();
    set_layer(root);
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
