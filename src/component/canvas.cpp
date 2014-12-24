#include <component/canvas.hpp>

// Render graphical object, by pointer.
void cosmodon::component::canvas::render(graphic *object)
{
    object->render(this);
}

// Render graphical object, by reference.
void cosmodon::component::canvas::render(graphic &object)
{
    render(&object);
}
