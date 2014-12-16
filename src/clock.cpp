#include <clock.hpp>

// Constructor.
cosmodon::clock::clock()
{
    reset();
}

// Reset clock.
void cosmodon::clock::reset()
{
    m_point = m_clock.now();
}

// Retrieve elapsed seconds.
uint32_t cosmodon::clock::elapsed_seconds(bool restart)
{
    std::chrono::high_resolution_clock::duration result = (m_clock.now() - m_point);
    if (restart) {
        reset();
    }
    return std::chrono::duration_cast<std::chrono::seconds>(result).count();
}
