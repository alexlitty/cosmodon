#include <layer.hpp>

using namespace cosmodon;

// Layer constructor.
layer::base::base(settings s)
{
    set_settings(s);
}

// Layer destructor.
layer::base::~base()
{
    for (unsigned int i = 0; i < m_children.size(); i++) {
        delete m_children[i];
    }
}

// Set layer settings.
void layer::base::set_settings(settings s)
{
    // Irrlicht.
    m_irrlicht = s.irrlicht;
    if (m_irrlicht != nullptr) {
        m_driver = s.irrlicht->getVideoDriver();
        m_scene_manager = s.irrlicht->getSceneManager();
        m_scene_root = m_scene_manager->getRootSceneNode();
    } else {
        m_driver = nullptr;
        m_scene_manager = nullptr;
        m_scene_root = nullptr;
    }

    // Network context.
    m_network_context = s.network_context;
}
