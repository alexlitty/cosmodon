#ifndef COSMODON_BUFFER
#define COSMODON_BUFFER

#include <cstring>
#include "exception.hpp"

namespace cosmodon
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

        // Mode of operation the buffer was previously used. True for writing, false for reading.
        bool m_writing;

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
         * Copy Constructor.
         *
         * Copies the given buffer into current buffer.
         */
        buffer(const buffer &other);

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
         * An alias for reset().
         */
        void rewind();

        /**
         * Retrieves size of this buffer in bytes.
         */
        uint32_t size() const;

        /**
         * Alias for size().
         */
        uint32_t length() const;

        /**
         * Retrieves the amount of bytes remaining to be read or written, relative to the
         * cursor position.
         */
        uint32_t remaining() const;

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
         * Retrieves a read-only pointer to the current data, truncated to given amount of bytes.
         * If amount is 0, all data is returned.
         *
         * Cursor is moved in a similar fashion to read() or write(), unless amount is 0, then the
         * position is left unchanged.
         *
         * If amount is greater than 0, a pointer is returned to raw data which exists beyond the
         * specified amount (if available). It may be accessed, but the cursor will not update
         * to reflect your current position.
         *
         * Returns null if no data is available.
         */
        const void* get_data(uint32_t amount = 0);

        /**
         * Retrieves a copy of raw data with given length, starting at the cursor.
         *
         * If unable to do so, throws a Cosmodon error.
         */
        void read(void *&data, size_t length);

        /**
         * Retrieves a copy of data with length of the provided type, starting at the cursor.
         *
         * If unable to do so, throws a Cosmodon warning. Do not use this function for
         * complicated object types -- only types which are easily reproduced by binary.
         */
        template <typename T>
        void read(T &x);

        /**
         * Retrieves a copy of data as a string, starting at the cursor.
         *
         * @@@ See write(std::string).
         */
        void read(std::string &data);

        /**
         * Writes raw data to the buffer.
         *
         * If buffer is not large enough to store new data, it is resized to the required
         * length.
         */
        void write(const void *data, size_t length);

        /**
         * Writes object data to the buffer.
         *
         * See write(const void*, size_t).
         */
        template <typename T>
        void write(const T &data);

        /**
         * Writes a string to the buffer.
         *
         * Writes the size of the string, then each character as a byte. The string is not null
         * terminated.
         *
         * @@@ Must be less than 256 characters. No multi-byte characters.
         */
        void write(const std::string &data);

        /**
         * Retrieves the buffer contents as hexadecimal.
         *
         * Useful for debugging.
         */
        std::string dump() const;

        /**
         * Equivalent Operator.
         *
         * Returns true if both buffers have equal length and equivalent bytes, false otherwise.
         */
        bool operator ==(const buffer &other);

        /**
         * Inequivalent Operator.
         *
         * See operator==().
         */
        bool operator !=(const buffer &other);

        /**
         * Input Stream Operator.
         *
         * Writes object data to the buffer.
         */
        template <typename T>
        buffer& operator <<(const T &data);

        /**
         * Output Stream Operator.
         *
         * Reads object data from the buffer.
         */
        template <typename T>
        buffer& operator >>(T &data);
    };
}

// Read data from the buffer. @@@ More memory-friendly way to do this
template <typename T>
void cosmodon::buffer::read(T &x)
{
    void *data;
    read(data, sizeof(T));
    memcpy(&x, static_cast<T*>(data), sizeof(T));
}

// Write data to the buffer.
template <typename T>
void cosmodon::buffer::write(const T &data)
{
    write(&data, sizeof(T));
}

// Output stream operator. Reads data from buffer.
template <typename T>
cosmodon::buffer& cosmodon::buffer::operator>>(T &data)
{
    read(data);
    return *this;
}

// Input stream operator. Writes data to the buffer.
template <typename T>
cosmodon::buffer& cosmodon::buffer::operator<<(const T &data)
{
    write(data);
    return *this;
}

#endif
