#include <vertex.hpp>

// Vertices constructor.
cosmodon::vertices::vertices(cosmodon::primitive primitive)
{
    set_primitive(primitive);
}

// Sets the primitive of vertices.
void cosmodon::vertices::set_primitive(cosmodon::primitive primitive)
{
    m_primitive = primitive;
}

// Render vertices by passing internal vertices.
void cosmodon::vertices::render(cosmodon::component::canvas *object)
{
    object->render(m_primitive, m_vertices_raw, m_vertices.size());
}
