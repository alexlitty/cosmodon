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

        /**
         * Constructor.
         */
        color();
    };
}

#endif
