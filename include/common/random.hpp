#ifndef COSMODON_COMMON_RANDOM
#define COSMODON_COMMON_RANDOM

#include <ctime>
#include <random>

namespace cosmodon
{
    namespace random
    {
        /**
         * Seeds random operations with the current time.
         */
        void seed();

        /**
         * Seeds random operations.
         *
         * @param  value  Value to seed random operations with.
         */
        void seed(uint32_t value);

        /**
         * Generates a random integer.
         *
         * @param  min  Minimum random value.
         * @param  max  Maximum random value.
         *
         * @returns  Integer between minimum and maximum values, inclusive.
         */
        uint32_t integer(uint32_t min, uint32_t max);
    }
}

#endif
