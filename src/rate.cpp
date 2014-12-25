#include <rate.hpp>

// Constructor.
cosmodon::rate::rate() : m_count(0)
{

}

// Resets internal counter.
void cosmodon::rate::reset()
{
    m_clock.reset();
    m_count = 0;
}

// Tally an occurence.
void cosmodon::rate::tally(uint64_t count)
{
    m_count += count;
}

// Retrieve the current rate, and reset counter.
uint64_t cosmodon::rate::get()
{
    uint64_t result = (m_count * 1000) / m_clock.elapsed(cosmodon::unit::millisecond);
    reset();
    return result;
}
