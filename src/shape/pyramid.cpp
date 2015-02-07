#include <shape/pyramid.hpp>

// Constructor.
cosmodon::shape::pyramid::pyramid(cosmodon::number width, cosmodon::number height)
{
    cosmodon::number w = width / 2;
    cosmodon::vertex top(0, 0, height);
    cosmodon::vertex northeast(w, w, 0.1f);
    cosmodon::vertex northwest(-w, w, 0.1f);
    cosmodon::vertex southeast(w, -w, 0.1f);
    cosmodon::vertex southwest(-w, -w, 0.1f);

    // Base.
    m_vertices.add(northeast);
    m_vertices.add(northwest);
    m_vertices.add(southeast);

    m_vertices.add(southwest);
    m_vertices.add(southeast);
    m_vertices.add(northwest);

    // First side.
    m_vertices.add(top);
    m_vertices.add(northwest);
    m_vertices.add(northeast);

    // Second side.
    m_vertices.add(top);
    m_vertices.add(northwest);
    m_vertices.add(southwest);

    // Third side.
    m_vertices.add(top);
    m_vertices.add(southwest);
    m_vertices.add(southeast);

    // Fourth side.
    m_vertices.add(top);
    m_vertices.add(southeast);
    m_vertices.add(northeast);

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

// Get pyramid position.
cosmodon::vector cosmodon::shape::pyramid::get_position()
{
    cosmodon::vector result;
    for (uint8_t i = 0; i < m_vertices.size(); i++) {
        result.x += m_vertices[i].x;
        result.y += m_vertices[i].y;
        result.z += m_vertices[i].z;
    }
    return cosmodon::vector(0, 0, 0.5f);
}
