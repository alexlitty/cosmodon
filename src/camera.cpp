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

// Retrieves camera target.
cosmodon::vector cosmodon::camera::get_target() const
{
    return m_target;
}

// Updates the view matrix.
void cosmodon::camera::update_view()
{
    cosmodon::vector eye = get_position();

    // Construct z-axis.
    cosmodon::vector z = eye - m_target;
    z.normalize();

    // Prepare y-axis.
    cosmodon::vector y = m_orientation;

    // Construct x-axis.
    cosmodon::vector x = y * z;

    // Construct y-axis.
    y = z * x;

    // Normalize results.
    x.normalize();
    y.normalize();

    // Set view matrix.
    m_view.set(
        x.x, x.y, x.z, -x.dot(eye),
        y.x, y.y, y.z, -y.dot(eye),
        z.x, z.y, z.z, -z.dot(eye),
        0, 0, 0, 1.0f
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
