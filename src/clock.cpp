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
uint32_t cosmodon::clock::elapsed(cosmodon::unit unit, bool restart)
{
    // Determine result.
    std::chrono::high_resolution_clock::duration result;
    result = (m_clock.now() - m_point);

    // Restart clock, if requested.
    if (restart) {
        reset();
    }

    // Cast to correct time unit. @@@ Messy.
    if (unit == cosmodon::unit::second) {
        return std::chrono::duration_cast<std::chrono::seconds>(result).count();
    } else if (unit == cosmodon::unit::millisecond) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(result).count();
    } else if (unit == cosmodon::unit::microsecond) {
        return std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    } else if (unit == cosmodon::unit::nanosecond) {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(result).count();
    } else {
        return 0;
    }
}
