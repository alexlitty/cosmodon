#include <transformation.hpp>
#include <vector.hpp>

// Update result matrix.
void cosmodon::transformation::update()
{
    m_result = m_rotation_z * m_rotation_y * m_rotation_x * m_translation * m_scale;

    // @@@
    cosmodon::vector a(0, 0), b(1.0f, 1.0f);
    a = m_result * a;
    b = m_result * b;
}

// Perform a scaling.
void cosmodon::transformation::scale(number x, number y, number z)
{
    m_scale.scale(x, y, z);
    update();
}

// Perform a translation.
void cosmodon::transformation::translate(number x, number y, number z)
{
    m_translation.translate(x, y, z);
}

// Perform a translation.
void cosmodon::transformation::rotate(number x, number y, number z)
{
    m_rotation_x.rotate_x(x);
    m_rotation_y.rotate_y(y);
    m_rotation_z.rotate_z(z);
    update();
}

// Returns result matrix.
cosmodon::matrix& cosmodon::transformation::get_matrix()
{
    return m_result;
}

// Convert to matrix, outputting the result matrix.
cosmodon::transformation::operator matrix()
{
    return get_matrix();
}
