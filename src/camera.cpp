#include <camera.hpp>

// Sets the camera position.
void cosmodon::camera::set_position(number set_x, number set_y, number set_z)
{
    component::position::set_position(set_x, set_y, set_z);
    update_orientation();
}

// Sets the point where the camera should look.
void cosmodon::camera::set_orientation(cosmodon::vector target, cosmodon::vector up)
{
    // Save target.
    m_target = target;
    update_orientation();
}

// Sets vertical field of view.
void cosmodon::camera::set_fov(cosmodon::number degrees)
{
    m_fov = degrees * (cosmodon::math::pi / 180.0f);
    update_perspective();
}

// Sets aspect.
void cosmodon::camera::set_aspect(cosmodon::number aspect)
{
    m_aspect = aspect;
    update_perspective();
}

// Sets z clipping distance? @@@
void cosmodon::camera::set_z(cosmodon::number near, cosmodon::number far)
{
    m_z_near = near;
    m_z_far = far;
    update_perspective();
}

// Updates the orientation matrix.
void cosmodon::camera::update_orientation()
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

// Updates the perspective matrix.
void cosmodon::camera::update_perspective()
{
    // Check for invalid parameters.
    if (m_fov == 0 || m_aspect == 0 || (m_z_near - m_z_far) == 0) {
        m_perspective.identity();
        return;
    }

    // Prepare parameters.
    cosmodon::number f = (1 / cosmodon::math::tangent(m_fov / 2));

    // Set matrix.
    m_perspective.set(
        (f / m_aspect), 0, 0, 0,
        0, f, 0, 0,
        0, 0, ((m_z_far + m_z_near) / (m_z_near - m_z_far)), ((2*m_z_far*m_z_near)/(m_z_near - m_z_far)),
        0, 0, -1, 0
    );
}

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
