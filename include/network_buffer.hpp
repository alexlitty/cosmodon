#ifndef COSMODON_NETWORK_BUFFER
#define COSMODON_NETWORK_BUFFER

#include "exception.hpp"

namespace cosmodon
{
    namespace network
    {
        /**
         * Buffer to hold network data.
         *
         * The contents inside the buffer are not internally associated with any data type. The
         * data is raw binary.
         */
        class buffer
        {
        protected:
            // Data inside buffer.
            void *m_data;

            // Byte length of buffer.
            size_t m_length;

            // Data corresponding to cursor position.
            void *m_cursor_data;

            // Cursor position.
            uint32_t m_cursor_pos;

            /**
             * Updates cursor data pointer to match cursor position.
             *
             * Assumes cursor position does not exceed buffer length.
             */
            void cursor_update();

        public:
            /**
             * Constructor.
             *
             * If the provided length is positive, a buffer of this length is allocated. The
             * initial contents are undefined.
             */
            buffer(size_t new_length = 0);

            /**
             * Deconstructor.
             *
             * Clears the buffer, which frees the internal buffer.
             */
            ~buffer();

            /**
             * Clears the buffer.
             *
             * Frees the internal buffer and resets buffer length and cursor position.
             */
            void clear();

            /**
             * Resets the reading and writing cursor to the buffer beginning.
             */
            void reset();

            /**
             * Retrieves size of this buffer in bytes.
             */
            uint32_t size();

            /**
             * Resizes the buffer to the provided length. Internally, the current buffer is moved
             * to a new buffer of given length.
             *
             * As such, data is preserved as well as possible. If the new length exceeds the old
             * length, data beyond the old length is undefined. Data up to the old length otherwise
             * remains equivalent.
             *
             * The internal cursor is not reset unless old length exceeds new length, and cursor
             * now exceeds new length. In this case, cursor is set to the new end of the buffer.
             */
            void resize(size_t new_length);

            /**
             * Retrieves arbitrary data of given length.
             *
             * If unable to do so, throws a Cosmodon warning.
             */
            void read(void *data, size_t length);

            /**
             * Retrieves the next byte as an integer.
             */
            int8_t read_int8();

            /**
             * Retrieves the next byte as an unsigned integer.
             */
            uint8_t read_uint8();

            /**
             * Writes raw data to the buffer.
             *
             * If buffer is not large enough to store new data, it is resized to the required
             * length.
             */
            void write(void *data, size_t length);

            /**
             * Writes object data to the buffer.
             *
             * See other method candidate.
             */
            template <typename T>
            void write(T *data);
        };
    }
}

// Write data to the buffer.
template <typename T>
void cosmodon::network::buffer::write(T *data)
{
    write(data, sizeof(T));
}

#endif
