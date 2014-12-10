#ifndef COSMODON_NETWORK_SOCKET
#define COSMODON_NETWORK_SOCKET

#include <arpa/inet.h>
#include <cstring>
#include <ctime>
#include <sys/socket.h>
#include <unistd.h>

#include "exception.hpp"
#include "network_buffer.hpp"
#include "network_utility.hpp"

namespace cosmodon
{
    namespace network
    {
        namespace socket
        {
            /**
             * Prototype socket.
             *
             * Sending and receiving data is implemented by children.
             */
            class base
            {
            protected:
                // Bytes sent by this socket.
                uint32_t m_bytes_out;
                uint32_t m_bytes_out_total;

                // Bytes received by this socket.
                uint32_t m_bytes_in;
                uint32_t m_bytes_in_total;

                // Timer used to calculate bitrate.
                time_t m_bytes_timer;

            public:
                /**
                 * Constructor.
                 *
                 * Initializes bitrate and transfer calculations.
                 */
                base();

                /**
                 * Returns the amount of bytes sent by this socket.
                 */
                uint32_t bytes_out();

                /**
                 * Returns the amount of bytes received by this socket.
                 */
                uint32_t bytes_in();

                /**
                 * Returns outgoing throughput, in bytes per second.
                 */
                uint32_t rate_out();

                /**
                 * Returns incoming throughput, in bytes per second.
                 */
                uint32_t rate_in();
            };

            /**
             * A barebones UDP socket. This implementation is connectionless.
             *
             * Sending and receiving is not blocked.
             */
            class udp : public base
            {
            protected:
                // Internal socket.
                int m_socket;

                // Port this socket is associated with.
                uint16_t m_port;

                // Temporary buffer to handle data.
                void *m_buffer;

                // Temporary buffer length.
                size_t m_buffer_length;

            public:
                /**
                 * Constructor.
                 */
                udp(uint16_t port);

                /**
                 * Destructor.
                 */
                ~udp();

                /**
                 * Send a buffer to the network.
                 *
                 * Returns true if buffer successfully sent, false otherwise.
                 */
                bool send(network::buffer &x, std::string destination);

                /**
                 * Receive data from the network into a buffer.
                 *
                 * Returns true if a buffer is made available, false otherwise.
                 */
                bool receive(network::buffer &x, std::string &source);
            };
        }
    }
}

#endif
