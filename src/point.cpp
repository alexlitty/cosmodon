#include <point.hpp>

template <typename U>
cosmodon::point3<U>::point3(U init_x, U init_y, U init_z) : x(m_value[0]), y(m_value[1]), z(m_value[2])
{
    x = init_x;
    y = init_y;
    z = init_z;
}
