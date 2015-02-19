#include <transformation.hpp>
#include <vector.hpp>

// Update result matrix.
void cosmodon::transformation::update()
{
    //m_result = m_rotation_z * m_rotation_y * m_rotation_x * m_translation * m_scale;
    m_result = m_scale * m_translation * m_rotation_x * m_rotation_y * m_rotation_z;
}

// Perform a scaling.
void cosmodon::transformation::set_scale(number x, number y, number z)
{
    m_scale.scale(x, y, z);
    update();
}

// Perform an even scaling.
void cosmodon::transformation::set_scale(cosmodon::number s)
{
    set_scale(s, s, s);
}

// Perform a translation.
void cosmodon::transformation::translate(number x, number y, number z)
{
    m_translation.translate(x, y, z);
    update();
}

// Alias to perform a translation.
void cosmodon::transformation::move(number x, number y, number z)
{
    translate(x, y, z);
}

// Sets translation absolutely.
void cosmodon::transformation::set_position(cosmodon::number value_x, cosmodon::number value_y,
                                            cosmodon::number value_z)
{
    cosmodon::component::position::set_position(value_x, value_y, value_z);
    m_translation.identity();
    translate(value_x, value_y, value_z);
}

// Perform a rotation.
void cosmodon::transformation::rotate(number x, number y, number z)
{
    m_rotation_x.rotate_x(x);
    m_rotation_y.rotate_y(y);
    m_rotation_z.rotate_z(z);
    update();
}

// Returns result matrix.
const cosmodon::matrix& cosmodon::transformation::get_matrix() const
{
    return m_result;
}

// Convert to matrix, outputting the result matrix.
cosmodon::transformation::operator matrix()
{
    return get_matrix();
}

// Definition of standard transformation.
cosmodon::transformation cosmodon::no_transformation;
