#include <shape/base.hpp>

// @@@
#include <iostream>

// Render shape.
void cosmodon::shape::base::render(cosmodon::render::target *object) const
{
    object->render(this, get_matrix(), m_fill);
}

// Get position.
cosmodon::vector cosmodon::shape::base::get_position() const
{
    return get_center();
}

// Get center.
cosmodon::vector cosmodon::shape::base::get_center() const
{
    return cosmodon::vertices::get_center() * get_matrix();
}

// Set fill mode.
void cosmodon::shape::base::set_fill(bool fill)
{
    m_fill = fill;
}
