#include <camera.hpp>

// Sets the camera position.
void cosmodon::camera::set_position(number set_x, number set_y, number set_z)
{
    component::position::set_position(set_x, set_y, set_z);
}

/*// Sets the point where the camera should look.
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
}*/

// Sets the camera orientation.
void cosmodon::camera::set_orientation(cosmodon::vector target, cosmodon::vector up)
{
    cosmodon::vector eye, delta, s;

    // Normalize parameters.
    target = target.normalize();
    up = up.normalize();

    // Prepare delta vector.
    eye = get_position();
    delta = target - eye;
    delta = delta.normalize();

    // Prepare up and s vector.
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
void cosmodon::camera::set_perspective(number fov, number aspect, number z_near, number z_far)
{
    // Check for invalid parameters.
    if (fov == 0 || aspect == 0 || (z_near - z_far) == 0) {
        m_perspective.identity();
        return;
    }

    // Prepare parameters.
    cosmodon::number f = (1 / cosmodon::math::tangent(cosmodon::math::radians(fov) / 2));

    // Set matrix.
    m_perspective.set(
        (f / aspect), 0, 0, 0,
        0, f, 0, 0,
        0, 0, ((z_far + z_near) / (z_near - z_far)), ((2*z_far*z_near)/(z_near - z_far)),
        0, 0, -1, 0
    );

    /*cosmodon::number xy_max, x_min, y_min;
    cosmodon::number width, height, depth, q, qn;

    xy_max = z_near * cosmodon::math::tangent(cosmodon::math::radians(fov / 2));
    x_min = -xy_max;
    y_min = -xy_max;

    width = xy_max - x_min;
    height = xy_max - y_min;

    depth = z_far - z_near;
    q = -(z_far + z_near) / depth;
    qn = -2 * (z_far * z_near) / depth;

    width = (2 * z_near / width) / aspect;
    height = 2 * z_near / height;

    m_perspective.set(
        width, 0, 0, 0,
        0, height, 0, 0,
        0, 0, q, -1,
        0, 0, qn, 0
    );*/
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
