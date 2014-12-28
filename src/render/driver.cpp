#include <render.hpp>

uint32_t cosmodon::render::driver::get_fps() const
{
    return m_fps.get();
}
