#ifndef COSMODON_CLOCK
#define COSMODON_CLOCK

#include <chrono>

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
         */
        uint32_t elapsed_seconds(bool restart = false);
    };
}

#endif
