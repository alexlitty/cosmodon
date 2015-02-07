#include <vertex.hpp>

// Vertex constructor.
cosmodon::vertex::vertex(float init_x, float init_y, float init_z, cosmodon::color color)
  : cosmodon::vector(init_x, init_y, init_z), cosmodon::color(color)
{

}

// Vertex copy constructor.
cosmodon::vertex::vertex(const cosmodon::vertex &copy)
  : cosmodon::vector(copy.x, copy.y, copy.z), cosmodon::color(copy.r, copy.g, copy.b, copy.a)
{

}

// Vertex to string.
cosmodon::vertex::operator std::string() const
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

// Vertices constructor.
cosmodon::vertices::vertices(cosmodon::primitive primitive)
{
    set_primitive(primitive);
}

// Vertices destructor.
cosmodon::vertices::~vertices()
{

}

// Adds a vertex to the collection.
void cosmodon::vertices::add(const cosmodon::vertex& vertex, bool end)
{
    m_vertices.push_back(vertex);
    if (end) {
        refresh();
    }
}

// Recalculates information about this collection.
void cosmodon::vertices::refresh()
{
    cosmodon::vector result(0, 0, 0);
    cosmodon::number min_x = 0, min_y = 0, min_z = 0;
    cosmodon::number max_x = 0, max_y = 0, max_z = 0;

    // Defaults.
    if (m_vertices.size() == 0) {
        set_position(result);
    }

    // Position, if single vertex.
    if (m_vertices.size() == 1) {
        set_position(m_vertices[0]);
    }

    // Position, multiple vertices.
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
    set_position(result);
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

// Render vertices.
void cosmodon::vertices::render(cosmodon::render::target *target)
{
    target->render(this);
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
