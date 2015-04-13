#include <draw/canvas.hpp>

// Alias to render a collection of vertices.
void cosmodon::canvas::draw(const cosmodon::vertices *vertices, const cosmodon::transformation &transform)
{
    draw(vertices, transform.get_matrix());
}

// Draw a graphic.
void cosmodon::canvas::draw(const cosmodon::graphic *object)
{
    object->draw(this);
}
