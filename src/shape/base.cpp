#include <shape/base.hpp>

// Render shape.
void cosmodon::shape::base::render(cosmodon::render::target *object)
{
    object->render(this, *this);
}
