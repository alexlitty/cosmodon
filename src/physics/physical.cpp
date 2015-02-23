#include <physics/physical.hpp>

// Constructor.
cosmodon::physical::physical()
: m_velocity(0), m_acceleration(0), m_static(false)
{

}

// Sets velocity.
void cosmodon::physical::set_velocity(cosmodon::vector velocity)
{
    if (is_static()) {
        m_velocity = 0;
    } else {
        m_velocity = velocity;
    }
}

// Gets velocity.
cosmodon::vector cosmodon::physical::get_velocity() const
{
    return m_velocity;
}

// Sets acceleration.
void cosmodon::physical::set_acceleration(cosmodon::vector acceleration)
{
    if (is_static()) {
        m_acceleration = 0;
    } else {
        m_acceleration = acceleration;
    }
}

// Gets acceleration.
cosmodon::vector cosmodon::physical::get_acceleration() const
{
    return m_acceleration;
}

// Sets static status.
void cosmodon::physical::set_static(bool s)
{
    m_static = s;

    if (is_static()) {
        set_velocity(0);
        set_acceleration(0);
    }
}
