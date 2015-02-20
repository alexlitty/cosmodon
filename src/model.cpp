#include <model.hpp>

// Get position.
cosmodon::vector cosmodon::model::get_position() const
{
    return get_center();
}

// Get center.
cosmodon::vector cosmodon::model::get_center() const
{
    return cosmodon::vertices::get_center() * get_matrix();
}

// Set fill mode.
void cosmodon::model::set_fill(bool fill)
{
    m_fill = fill;
}

// Check fill mode.
bool cosmodon::model::is_fill() const
{
    return m_fill;
}

// Render model.
void cosmodon::model::render(cosmodon::render::target *object) const
{
    object->render(this, get_matrix(), m_fill);
}
