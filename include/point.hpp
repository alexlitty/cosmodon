#ifndef COSMODON_POINT
#define COSMODON_POINT

#include <cstdint>

namespace cosmodon
{
    /**
     * A point, representing a three dimmensional location.
     *
     * When used in two dimmensional environments, the Z axis still represents depth.
     */
    class point
    {
    public:
        // X axis.
        float x;

        // Y axis.
        float y;

        // Z axis.
        float z;

        /**
         * Constructor.
         */
        point(float init_x = 0, float init_y = 0, float init_z = 0);
    };
}

#endif
