#include <shape/triangle.hpp>

// Constructor.
cosmodon::shape::triangle::triangle()
{
    cosmodon::vertex vertex(0, 0, 1, 1);
    m_vertices.add(vertex);
    vertex.y = 1;
    m_vertices.add(vertex);
    vertex.x = 1;
    m_vertices.add(vertex);
}

// Render triangle.
void cosmodon::shape::triangle::render(cosmodon::component::canvas &object)
{
    object.render(m_vertices);
}
