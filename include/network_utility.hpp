#ifndef COSMODON_NETWORK_UTILITY
#define COSMODON_NETWORK_UTILITY

#include <string>
#include "zmq/zmq.h"
#include "exception.hpp"

namespace cosmodon
{
    namespace network
    {
        // Ports.
        namespace PORT
        {
            extern const char* INTERNAL;
            extern const char* EXTERNAL;
        }

        /**
         * Function used by 0MQ to free memory.
         *
         * Particularly used when handling 0MQ messages. These messages assume ownership of
         * provided memory, and require a callback function to be freed.
         */
        void zfree(void *data, void *hint);

        /**
         * Returns a well-formed TCP endpoint address.
         */
        const char* endpoint(const char* address, const char* port, const char* method = "tcp");

        /**
         * Returns the current 0MQ error as a string.
         */
        const char* error();

        /**
         * Converts bits into a more appropriate statistic.
         *
         * If bytes is true, returns statistic in bytes instead of bits.
         */
        std::string bits_readable(unsigned int count, bool bytes = false);
    }
}

#endif
