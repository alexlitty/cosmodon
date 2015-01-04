#include <shape/pyramid.hpp>

// Constructor.
cosmodon::shape::pyramid::pyramid(cosmodon::number width, cosmodon::number height)
{
    cosmodon::number w = width / 2;
    cosmodon::vertex top(0, 0, height);
    cosmodon::vertex up_right(w, w);
    cosmodon::vertex up_left(-w, w);
    cosmodon::vertex down_right(w, -w);
    cosmodon::vertex down_left(-w, -w);

    // Base.
    m_vertices.add(up_left);
    m_vertices.add(up_right);
    m_vertices.add(down_right);

    m_vertices.add(up_left);
    m_vertices.add(down_right);
    m_vertices.add(down_left);

    // First side.
    m_vertices.add(up_left);
    m_vertices.add(up_right);
    m_vertices.add(top);

    // Second side.
    m_vertices.add(up_left);
    m_vertices.add(down_left);
    m_vertices.add(top);

    // Third side.
    m_vertices.add(down_left);
    m_vertices.add(down_right);
    m_vertices.add(top);

    // Fourth side.
    m_vertices.add(down_right);
    m_vertices.add(up_right);
    m_vertices.add(top);

    // Assign vertex colors.
    for (uint8_t i = 0; i < m_vertices.size(); i++) {
        m_vertices[i].r = 255 - (i * 10);
        m_vertices[i].g = 255 - (i * 10);
        m_vertices[i].b = 150;
    }
}

// Render pyramid.
void cosmodon::shape::pyramid::render(cosmodon::render::target *target)
{
    target->render(&m_vertices, get_matrix());
}
