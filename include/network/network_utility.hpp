#ifndef COSMODON_NETWORK_UTILITY
#define COSMODON_NETWORK_UTILITY

#include <string>
#include "../common/exception.hpp"

namespace cosmodon
{
    namespace network
    {
        /**
         * Converts bits into a more appropriate statistic.
         *
         * If bytes is true, returns statistic in bytes instead of bits.
         */
        std::string bits_readable(unsigned int count, bool bytes = false);
    }
}

#endif
