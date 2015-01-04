#include "component/position.hpp"

// Move object relative to its current position.
void cosmodon::component::position::move(number move_x, number move_y, number move_z)
{
    set_position((x + move_x), (y + move_y), (z + move_z));
}

// Set object position.
void cosmodon::component::position::set_position(number set_x, number set_y, number set_z)
{
    x = set_x;
    y = set_y;
    z = set_z;
}

// Get object position.
cosmodon::vector cosmodon::component::position::get_position() const
{
    return cosmodon::vector(x, y, z);
}
