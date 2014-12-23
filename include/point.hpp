#ifndef COSMODON_POINT
#define COSMODON_POINT

#include <cstdint>

namespace cosmodon
{
    /**
     * A point, representing a spot inside an area.
     *
     * The dimmensions of the point are provided by the first template parameter. For example, a
     * two-dimmensional point is represented by passing the integer 2.
     *
     * Values have an undefined default value, and should be assigned immediately.
     */
    template <uint8_t T, typename U = float>
    class point
    {
    protected:
        // Collection of internal values.
        U m_value[T];
    };

    /**
     * A specialized three-dimmensional point.
     */
    template <typename U = float>
    class point3 : public point<3>
    {
    public:
        // First value.
        U &x;

        // Second value.
        U &y;

        // Third value.
        U &z;

        /**
         * Constructor.
         */
        point3(U init_x, U init_y, U init_z);
    };
}

#endif
