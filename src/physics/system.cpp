#include <physics/system.hpp>

// Adds an object to this system.
void cosmodon::physics::system::add(cosmodon::physical &object)
{
    if (!is_inside(object)) {
        m_objects.push_back(&object);
    }
}

// Checks if an object is inside the system.
bool cosmodon::physics::system::is_inside(cosmodon::physical &object) const
{
    for (uint16_t i = 0; i < m_objects.size(); i++) {
        if (m_objects[i] == &object) {
            return true;
        }
    }
    return false;
}

// Removes an object from this system.
void cosmodon::physics::system::remove(cosmodon::physical &object)
{
    for (uint16_t i = 0; i < m_objects.size(); i++) {
        if (m_objects[i] == &object) {
            m_objects.erase(m_objects.begin() + i);
            return;
        }
    }
}
