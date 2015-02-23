#include <physics/physical.hpp>

// Constructor.
cosmodon::physical::physical()
: m_velocity(0), m_acceleration(0)
{

}

// Sets velocity.
void cosmodon::physical::set_velocity(cosmodon::vector velocity)
{
    m_velocity = velocity;
}

// Gets velocity.
cosmodon::vector cosmodon::physical::get_velocity() const
{
    return m_velocity;
}

// Sets acceleration.
void cosmodon::physical::set_acceleration(cosmodon::vector acceleration)
{
    m_acceleration = acceleration;
}

// Gets acceleration.
cosmodon::vector cosmodon::physical::get_acceleration() const
{
    return m_acceleration;
}
