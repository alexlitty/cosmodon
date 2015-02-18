#include <camera.hpp>

// Camera constructor.
cosmodon::camera::camera()
: m_target(0, 0, 0),
  m_orientation(0, 0.5f, 0),
  m_fov(90),
  m_aspect(0),
  m_near(0),
  m_far(1)
{

}

// Sets the camera position.
void cosmodon::camera::set_position(number set_x, number set_y, number set_z)
{
    component::position::set_position(set_x, set_y, set_z);
    update_view();
}

// Sets vertical field of view.
void cosmodon::camera::set_fov(cosmodon::number degrees)
{
    m_fov = degrees;
    update_projection();
}

// Sets aspect.
void cosmodon::camera::set_aspect(cosmodon::number aspect)
{
    m_aspect = aspect;
    update_projection();
}

// Sets clipping distance.
void cosmodon::camera::set_clipping(cosmodon::number near, cosmodon::number far)
{
    m_near = near;
    m_far = far;
    update_projection();
}

// Sets camera orientation.
void cosmodon::camera::set_orientation(vector orientation)
{
    m_orientation = orientation;
    update_view();
}

// Sets camera target.
void cosmodon::camera::set_target(vector target)
{
    m_target = target;
    update_view();
}

// Updates the view matrix.
void cosmodon::camera::update_view()
{
    cosmodon::vector eye, delta, s, target, up;

    // Normalize parameters.
    target = m_target.normalize();
    up = m_orientation.normalize();

    // Prepare delta vector.
    eye = get_position();
    delta = target - eye;
    delta = delta.normalize();

    // Prepare up and s vector.
    s = delta * up;
    up = s * delta;

    // Set matrix.
    m_view.set(
        s.x, s.y, s.z, -eye.x,
        up.x, up.y, up.z, -eye.y,
        -delta.x, -delta.y, -delta.z, -eye.z,
        0, 0, 0, 1
    );
}

// Updates the projection matrix.
void cosmodon::camera::update_projection()
{
    // Check for invalid parameters.
    if (m_fov == 0 || m_aspect == 0 || (m_near - m_far) == 0) {
        m_projection.identity();
        return;
    }

    // Prepare parameters.
    cosmodon::number f = (1 / cosmodon::math::tangent(cosmodon::math::radians(m_fov) / 2));

    // Set matrix.
    m_projection.set(
        (f / m_aspect), 0, 0, 0,
        0, f, 0, 0,
        0, 0, ((m_far + m_near) / (m_near - m_far)), ((2*m_far*m_near)/(m_near - m_far)),
        0, 0, -1, 0
    );
}

// Retrieves the orientation matrix.
const cosmodon::matrix& cosmodon::camera::get_view() const
{
    return m_view;
}

// Retrieves the perspective matrix.
const cosmodon::matrix& cosmodon::camera::get_projection() const
{
    return m_projection;
}
