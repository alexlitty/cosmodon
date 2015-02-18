#include <render/target.hpp>

// Alias to render a collection of vertices.
void cosmodon::render::target::render(const cosmodon::vertices *vertices, const cosmodon::transformation &transform)
{
    render(vertices, transform.get_matrix());
}

// Render a graphic.
void cosmodon::render::target::render(const cosmodon::graphic *object)
{
    object->render(this);
}
