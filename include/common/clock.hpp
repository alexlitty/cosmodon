#ifndef COSMODON_CLOCK
#define COSMODON_CLOCK

#include <chrono>
#include "unit.hpp"

namespace cosmodon
{
    /**
     * A clock to measure elapsed times.
     */
    class clock
    {
        // Internal clock mechanism.
        std::chrono::high_resolution_clock m_clock;

        // Previous time point, used to measure elapsed times.
        std::chrono::high_resolution_clock::time_point m_point;

    public:
        /**
         * Constructor.
         *
         * Starts the internal clock.
         */
        clock();

        /**
         * Reset clock, to start measuring from the current time.
         */
        void reset();

        /**
         * Retrieve the elapsed seconds since the previous time.
         *
         * Resets the clock if argument is true.
         *
         * If an invalid unit is given, returns 0.
         */
        uint32_t elapsed(cosmodon::unit unit = cosmodon::unit::second, bool restart = false);
    };
}

#endif
