#ifndef COSMODON_NETWORK_SOCKET
#define COSMODON_NETWORK_SOCKET

#include <cstring>
#include "debug.hpp"
#include "exception.hpp"
#include "network_utility.hpp"
#include "network_message.hpp"

namespace cosmodon
{
    namespace network
    {
        /**
         * Generic Socket.
         *
         * Heavily wrapped around 0MQ.
         */
        class socket
        {
        protected:
            // Socket this class wraps.
            void *m_socket;

            /**
             * Retrieve 0MQ socket option.
             *
             * Wrap nicer functions around this this function.
             */
            void get_opt(int option, int &value);

        public:
            /**
             * Type of 0MQ socket.
             */
            enum type
            {
                REQUEST = ZMQ_REQ,
                REPLY = ZMQ_REP,
                PUBLISH = ZMQ_PUB,
                SUBSCRIBE = ZMQ_SUB,
                PULL = ZMQ_PULL,
                PUSH = ZMQ_PUSH,
                PAIR = ZMQ_PAIR,
                STREAM = ZMQ_STREAM,
            };

            /**
             * Constructor.
             */
            socket(void *context, int type);

            /**
             * Destructor.
             */
            ~socket();

            /**
             * Establish a connection over this socket.
             */
            void connect(const char *endpoint);

            /**
             * Bind this socket to an endpoint.
             */
            void bind(const char *endpoint);

            /**
             * Send a message over this socket.
             *
             * @@@ Make parameter const
             */
            bool send(network::message* msg);

            /**
             * Receive a message over this socket.
             *
             * Given parameter will be deleted.
             */
            bool receive(network::message &msg);

            /**
             * Check if more message parts are available to be received.
             *
             * True if so. False otherwise.
             */
            bool more_incoming();

            /**
             * Set outgoing high water mark.
             */
            void set_send_hwm(unsigned int value);

            /**
             * Set incoming high water mark.
             */
            void set_receive_hwm(unsigned int value);

            /**
             * Set subscription filter.
             */
            void set_filter(const void *value);

            /**
             * Unset subscription filter.
             */
            void unset_filter(const void *value);

            /**
             * Set identity.
             */
            void set_identity(const void *value);

            /**
             * Get identity.
             */
            void get_identity(const void *value);

            /**
             * Set lingering period.
             */
            void set_linger(unsigned int value);
        };
    }
}

#endif
