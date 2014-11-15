#include <layer.hpp>

using namespace cosmodon;

// Layer constructor.
layer::base::base(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *scene_manager, void *context)
  : m_driver(driver), m_scene_manager(scene_manager), m_context(context)
{
    m_scene_root = scene_manager->getRootSceneNode();
}

// Set network context.
void layer::base::set_context(void *context)
{
    m_context = context;
}
