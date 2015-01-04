#include <camera.hpp>

// Sets the camera position.
void cosmodon::camera::set_position(number set_x, number set_y, number set_z)
{
    component::position::set_position(set_x, set_y, set_z);
    update_view();
}

// Sets the point where the camera should look.
void cosmodon::camera::set_orientation(cosmodon::vector target, cosmodon::vector up)
{
    // Save target.
    m_target = target;
    update_view();
}

// Updates the view matrix.
void cosmodon::camera::update_view()
{
    cosmodon::vector eye = get_position();
    cosmodon::vector delta = m_target - eye;
    cosmodon::vector up;
    cosmodon::vector s;

    // Prepare vectors.
    delta = delta.normalize();
    up = m_up.normalize();
    s = delta * up;
    up = s * delta;

    // Set matrix.
    m_orientation.set(
        s.x, s.y, s.z, -eye.x,
        up.x, up.y, up.z, -eye.y,
        -delta.x, -delta.y, -delta.z, -eye.z,
        0, 0, 0, 1
    );
}

// @@@
#include <iostream>

// Retrieves the orientation matrix.
const cosmodon::matrix& cosmodon::camera::get_orientation() const
{
    return m_orientation;
}

// Retrieves the perspective matrix.
const cosmodon::matrix& cosmodon::camera::get_perspective() const
{
    return m_perspective;
}
