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

        // Returns a well-formed TCP endpoint address.
        const char* endpoint(const char* address, const char* port, const char* method = "tcp");

        // Returns the current ZMQ error as a string.
        const char* error();
    }
}

#endif
