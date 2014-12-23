#ifndef COSMODON_COLOR
#define COSMODON_COLOR

#include <cstdint>

namespace cosmodon
{
    /**
     * A color container.
     */
    class color
    {
    public:
        // Red color part.
        uint8_t r;

        // Green color part.
        uint8_t g;

        // Blue color part.
        uint8_t b;

        // Alpha part.
        uint8_t a;

        /**
         * Constructor.
         */
        color(uint8_t init_r = 0, uint8_t init_g = 0, uint8_t init_b = 0, uint8_t init_a = 255);
    };
}

#endif
