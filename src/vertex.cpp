#include <vertex.hpp>

// Vertex constructor.
cosmodon::vertex::vertex(float init_x, float init_y, float init_z, float init_a)
  : cosmodon::point(init_x, init_y, init_z), a(init_a)
{
}

// Vertices constructor.
cosmodon::vertices::vertices(cosmodon::primitive primitive) : m_vertices_raw(nullptr)
{
    set_primitive(primitive);
}

// Vertices destructor.
cosmodon::vertices::~vertices()
{
    delete [] m_vertices_raw;
}

// Adds a vertex to the collection.
void cosmodon::vertices::add(const cosmodon::vertex& vertex)
{
    m_vertices.push_back(vertex);
}

// Sets the primitive of vertices.
void cosmodon::vertices::set_primitive(cosmodon::primitive primitive)
{
    m_primitive = primitive;
}

// Render vertices.
void cosmodon::vertices::render(cosmodon::component::canvas *object)
{
    delete [] m_vertices_raw;

    // Check if vertices are available.
    if (m_vertices.size() == 0) {
        return;
    }

    // Prepare raw vertices.
    m_vertices_raw = new float[m_vertices.size() * 4];
    for (uint32_t i = 0; i < m_vertices.size(); i++) {
        m_vertices_raw[i + 0] = m_vertices[i].x;
        m_vertices_raw[i + 1] = m_vertices[i].y;
        m_vertices_raw[i + 2] = m_vertices[i].z;
        m_vertices_raw[i + 3] = m_vertices[i].a;
    }

    // Render raw vertices.
    object->render(m_primitive, m_vertices_raw, m_vertices.size());
}

// Data access operator.
cosmodon::vertex& cosmodon::vertices::operator [](const uint32_t index)
{
    return m_vertices[index];
}

// Const data access operator.
const cosmodon::vertex& cosmodon::vertices::operator [](const uint32_t index) const
{
    return m_vertices[index];
}
