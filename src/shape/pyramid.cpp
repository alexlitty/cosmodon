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
    add(northeast);
    add(northwest);
    add(southeast);

    add(southwest);
    add(southeast);
    add(northwest);

    // First side.
    add(top);
    add(northwest);
    add(northeast);

    // Second side.
    add(top);
    add(northwest);
    add(southwest);

    // Third side.
    add(top);
    add(southwest);
    add(southeast);

    // Fourth side.
    add(top);
    add(southeast);
    add(northeast);

    // Assign vertex colors.
    for (uint8_t i = 0; i < m_vertices.size(); i++) {
        m_vertices[i].r = 255 - (i * 10);
        m_vertices[i].g = 255 - (i * 10);
        m_vertices[i].b = 150;
    }
}
