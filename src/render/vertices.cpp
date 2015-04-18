#include <render/vertices.hpp>

// Vertices constructor.
cosmodon::vertices::vertices(cosmodon::primitive primitive)
{
    set_primitive(primitive);
}

// Vertices destructor.
cosmodon::vertices::~vertices()
{

}

// Clears this collection of all vertices.
void cosmodon::vertices::clear()
{
    resize(0);
}

// Adds a vertex to the collection.
void cosmodon::vertices::add(cosmodon::number init_x, cosmodon::number init_y, cosmodon::number init_z)
{
    cosmodon::vertex vert(init_x, init_y, init_z);
    add(vert);
}

// Adds a vertex to the collection.
void cosmodon::vertices::add(const cosmodon::vertex& vert)
{
    m_vertices.push_back(vert);
}

// Adds a set of vertices to the collection.
void cosmodon::vertices::add(const cosmodon::vertices& verts)
{
    for (uint32_t i = 0; i < verts.size(); i++) {
        add(verts[i] * verts.m_result);
    }
}

// Retrieves center vertex.
cosmodon::vector cosmodon::vertices::get_center() const
{
    cosmodon::vector result(0, 0, 0);
    cosmodon::number min_x = 0, min_y = 0, min_z = 0;
    cosmodon::number max_x = 0, max_y = 0, max_z = 0;

    // No vertices.
    if (m_vertices.size() == 0) {
        return result;
    }

    // Single vertex.
    else if (m_vertices.size() == 1) {
        result = m_vertices[0];
        return result;
    }

    // Multiple vertices.
    for (uint8_t i = 0; i < m_vertices.size(); i++) {
        if (min_x > m_vertices[i].x) {
            min_x = m_vertices[i].x;
        }
        if (max_x < m_vertices[i].x) {
            max_x = m_vertices[i].x;
        }

        if (min_y > m_vertices[i].y) {
            min_y = m_vertices[i].y;
        }
        if (max_y < m_vertices[i].y) {
            max_y = m_vertices[i].y;
        }

        if (min_z > m_vertices[i].z) {
            min_z = m_vertices[i].z;
        }
        if (max_z < m_vertices[i].z) {
            max_z = m_vertices[i].z;
        }
    }
    result.x = (min_x + max_x) / 2;
    result.y = (min_y + max_y) / 2;
    result.z = (min_z + max_z) / 2;
    return result;
}

// Retrieve the amount of vertices inside this collection.
uint32_t cosmodon::vertices::size() const
{
    return m_vertices.size();
}

// Resize the vertex count inside this collection.
void cosmodon::vertices::resize(uint32_t amount)
{
    m_vertices.resize(amount);
}

// Sets the primitive of vertices.
void cosmodon::vertices::set_primitive(cosmodon::primitive primitive)
{
    m_primitive = primitive;
}
