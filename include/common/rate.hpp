#ifndef COSMODON_RATE
#define COSMODON_RATE

#include "clock.hpp"

namespace cosmodon
{
    /**
     * A class to measure the rate of some criteria occurring.
     *
     * Common applications include measuring Frames Per Second, and Socket transfer rates.
     */
    class rate
    {
    protected:
        // Internal clock used to measure elapsed time.
        clock m_clock;

        // Counter to measure occurrences.
        uint64_t m_count;

    public:
        /**
         * Constructor.
         */
        rate();

        /**
         * Resets the internal counter.
         */
        void reset();

        /**
         * Tally an occurrence.
         */
        void tally(uint64_t count = 1);

        /**
         * Retrieve the current rate, and reset the internal counter.
         */
        uint64_t get();
    };
}

#endif
