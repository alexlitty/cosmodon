#include <render/target.hpp>

// Render a graphic.
void cosmodon::render::target::render(cosmodon::graphic *object)
{
    object->render(this);
}
