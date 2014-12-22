#ifndef COSMODON_SOCKET
#define COSMODON_SOCKET

#include <arpa/inet.h>
#include <cstring>
#include <ctime>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include "clock.hpp"
#include "buffer.hpp"
#include "exception.hpp"

namespace cosmodon
{
    namespace socket
    {
        /**
         * Socket mode of operation.
         */
        enum class mode : uint8_t
        {
            BIDIRECTIONAL,
            INPUT,
            OUTPUT,
        };

        /**
         * Prototype socket.
         *
         * Sending and receiving data is implemented by children.
         */
        class base
        {
        private:
            // Total bytes sent, updated internally.
            uint32_t m_bytes_out_total;
            uint32_t m_bytes_in_total;

            // Timers used to calculate rate of transfer.
            cosmodon::clock m_bytes_out_timer;
            cosmodon::clock m_bytes_in_timer;

        protected:
            // Recent count of bytes sent and received, updated by children.
            uint32_t m_bytes_out;
            uint32_t m_bytes_in;

        public:
            /**
             * Constructor.
             *
             * Initializes bitrate and transfer calculations.
             */
            base();

            /**
             * Returns the amount of bytes sent from this socket.
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
         * A barebones UDP socket, which operates in input and output modes.
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

            // Internal address info storage.
            addrinfo *m_address_info;

            /**
             * Retrieve address information.
             *
             * Used internally with Unix sockets.
             *
             * Address information is generated and stored inside the class before being returned.
             * The information is freed upon class destruction.
             */
            const addrinfo* get_address_info(std::string address);

        public:
            /**
             * Constructor.
             */
            udp(uint16_t port, size_t buffer_length = 1024);

            /**
             * Destructor.
             */
            ~udp();

            /**
             * Send a buffer to the network.
             *
             * Returns true if buffer successfully sent, false otherwise.
             */
            bool send(cosmodon::buffer &buff, std::string destination);

            /**
             * Receive data from the network into a buffer.
             *
             * Returns true if a buffer is made available, false otherwise.
             */
            bool receive(cosmodon::buffer &buff, std::string &source);
        };
    }
}

#endif
