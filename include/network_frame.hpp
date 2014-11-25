#ifndef COSMODON_NETWORK_FRAME
#define COSMODON_NETWORK_FRAME

#include <zmq/zmq.h>

namespace cosmodon
{
    namespace network
    {
        namespace frame
        {
            /**
             * Collection of possible frame formats.
             *
             * Intentionally defined in this header file.
             */
            enum class FORMAT : char
            {
                INVALID,
                ACK,
                DATA,
            };

            /**
             * Basic and generic frame, used to compose a message.
             *
             * Frames are further composed of parts.
             */
            class base
            {
            private:
                // Internal counter. Used to count in and out parts.
                unsigned char m_current;

            protected:
                // Format of this frame.
                FORMAT m_format;

                // Count of parts that compose this frame.
                unsigned char m_parts;

                // Ideal size of this frame, in bits.
                unsigned int m_size;

                /**
                 * Provides a part by its index value, via arguments.
                 *
                 * The given index will always be within valid range.
                 */
                virtual void get_part(unsigned char index, const void *&data, size_t &length) = 0;

                /**
                 * Sets a part by its index value, via arguments.
                 *
                 * The given index will always be within valid range.
                 */
                virtual bool set_part(unsigned char index, const void *data, size_t length) = 0;

            public:
                /**
                 * Constructor.
                 */
                base(FORMAT format = FORMAT::INVALID, unsigned char parts = 0);

                /**
                 * Destructor.
                 */
                virtual ~base();

                /**
                 * Resets the internal counter.
                 */
                void reset();

                /**
                 * Returns the complete size of this frame, in bits.
                 */
                unsigned int size();

                /**
                 * Checks if more parts are available to output or input.
                 */
                bool more();

                /**
                 * Provides the next available part.
                 */
                void get_next_part(const void *&data, size_t &length);

                /**
                 * Sets the next available part.
                 *
                 * Returns true if the part is successfully set, false otherwise.
                 */
                bool set_next_part(const void *data, size_t length);

                /**
                 * Retrieves the frame part of this header.
                 */
                void get_header_part(const void *&data, size_t &length);
            };

            /**
             * Acknowledgement Frame.
             *
             * If the Request For Return is true, this frame acts as a ping. Otherwise it acts as
             * the return of a ping -- a pong.
             */
            class ack : public base
            {
            protected:
                bool m_request_return;

                /**
                 * Get part by index.
                 */
                void get_part(unsigned char index, const void *&data, size_t &length);

                /**
                 * Set part by index.
                 */
                bool set_part(unsigned char index, const void *data, size_t length);

            public:
                /**
                 * Constructor.
                 */
                ack(bool request_return = false);
                
                /**
                 * Set request return.
                 */
                void set_request_return(bool request_return);

                /**
                 * Get request return.
                 */
                bool get_request_return();
            };

            /**
             * Data Frame.
             *
             * Used to transfer larger amounts of unspecified bits.
             *
             * @@@ This really should not be used.
             */
            class data : public base
            {
            protected:
                void *m_x;
                size_t m_length;
                void get_part(unsigned char index, const void *&x, size_t &length);
                bool set_part(unsigned char index, const void *dx, size_t length);

            public:
                /**
                 * Constructor.
                 */
                data(const void *x, size_t length);

                /**
                 * Set data and data length.
                 */
                void set(const void *x, size_t length);
            };
        }
    }
}

#endif
