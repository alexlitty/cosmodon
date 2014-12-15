#include <component.hpp>

using namespace cosmodon;

// Constructor.
component::model::model(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id)
  : irr::scene::ISceneNode(parent, mgr, id)
{

}

// Return boundaries of model.
const irr::core::aabbox3d<irr::f32>& component::model::getBoundingBox() const
{
  return m_bounding_box;
}
