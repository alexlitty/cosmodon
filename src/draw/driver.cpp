#include <draw/driver.hpp>

uint32_t cosmodon::draw::driver::get_fps() const
{
    return m_fps.get();
}
