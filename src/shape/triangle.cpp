#include <shape/triangle.hpp>

// @@@
#include <iostream>

// Constructor.
cosmodon::shape::triangle::triangle()
{
    cosmodon::vertex vertex(0.5f, 0.5f, 0, cosmodon::red);
    m_vertices.add(vertex);
    vertex.y = 0.0f;
    m_vertices.add(vertex);
    vertex.x = 0.0f;
    m_vertices.add(vertex);
}

// Render triangle.
void cosmodon::shape::triangle::render(cosmodon::render::target *target)
{
    target->render(&m_vertices);
}
