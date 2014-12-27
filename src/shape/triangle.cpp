#include <shape/triangle.hpp>

// Constructor.
cosmodon::shape::triangle::triangle()
{
    cosmodon::vertex vertex(0, 0, 0, cosmodon::red);
    m_vertices.add(vertex);
    vertex.y = 100;
    m_vertices.add(vertex);
    vertex.x = 100;
    m_vertices.add(vertex);
}

// Render triangle.
void cosmodon::shape::triangle::render(cosmodon::render::target *target)
{
    target->render(&m_vertices);
}
