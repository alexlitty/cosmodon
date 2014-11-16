#ifndef NETWORK_CONTEXT
#define NETWORK_CONTEXT

#include "zmq/zmq.h"
#include "exception.hpp"
#include "network_socket.hpp"
#include "network_utility.hpp"

namespace cosmodon
{
    namespace network
    {
        /**
         * A context used to create sockets and transfer messages.
         */
        class context
        {
        protected:
            void *m_zmq_context;

        public:
            /**
             * Constructor.
             *
             * Initializes a context or throws a fatal exception.
             */
            context();

            /**
             * Destructor.
             */
            ~context();

            /**
             * Create socket.
             *
             * Parameter is a socket type, from an enum in the socket class.
             *
             * Throws a fatal exception is socket could not be created.
             */
            socket* create(int type);
        };
    }
}

#endif
