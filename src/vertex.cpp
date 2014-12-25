#include <vertex.hpp>

// Vertex constructor.
cosmodon::vertex::vertex(float init_x, float init_y, float init_z, float init_a)
  : cosmodon::point(init_x, init_y, init_z), a(init_a)
{

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
void cosmodon::vertices::add(const cosmodon::vertex& vertex)
{
    m_vertices.push_back(vertex);
}

// Retrieve the amount of vertices inside this collection.
uint32_t cosmodon::vertices::size() const
{
    return m_vertices.size();
}

// Sets the primitive of vertices.
void cosmodon::vertices::set_primitive(cosmodon::primitive primitive)
{
    m_primitive = primitive;
}

// Render vertices.
void cosmodon::vertices::render(cosmodon::component::canvas *object)
{
    object->render(*this);
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
