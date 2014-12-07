#include <cstring>
#include <network_buffer.hpp>

using namespace cosmodon::network;

// Buffer constructor.
buffer::buffer(size_t new_length)
{
    if (new_length <= 0) {
        m_data = nullptr;
        m_length = 0;
    } else {
        m_data = malloc(new_length);
    }
    reset();
}

// Buffer destructor.
buffer::~buffer()
{
    clear();
}

// Updates cursor.
void buffer::cursor_update()
{
    if (m_data == nullptr) {
        m_cursor_pos = 0;
        m_cursor_data = nullptr;
    } else {
        m_cursor_data = static_cast<char*>(m_data) + m_cursor_pos;
    }
}

// Clear buffer.
void buffer::clear()
{
    free(m_data);
    m_data = nullptr;
    m_length = 0;
    reset();
}

// Resets cursor position.
void buffer::reset()
{
    m_cursor_pos = 0;
    m_cursor_data = m_data;
}

// Returns size of this buffer in bytes.
uint32_t buffer::size()
{
    return m_length;
}

// Resize buffer.
void buffer::resize(size_t new_length)
{
    void *old_data;
    size_t old_length;

    // Nonpositive length: Destroy buffer.
    if (new_length <= 0) {
        clear();
    }
    
    // Positive length: Move buffer to reallocation.
    else {
        old_data = m_data;
        old_length = m_length;
        m_length = new_length;

        // Transfer buffer.
        m_data = malloc(new_length);
        if (new_length > old_length) {
            memcpy(m_data, old_data, old_length);
        } else {
            memcpy(m_data, old_data, new_length);
        }

        // Update cursor position.
        if (m_cursor_pos > new_length) {
            m_cursor_pos = new_length;
        }
        cursor_update();
    }
}

// Retrieves data of given length.
void* buffer::read(size_t length)
{
    void *data;

    // Check for overflow.
    if ((m_length - m_cursor_pos) < length) {
        throw cosmodon::exception::error("Network Buffer Overflow");
    }

    // Copy data.
    data = malloc(length);
    memcpy(data, m_cursor_data, length);

    // Update cursor, clean up.
    m_cursor_pos += length;
    cursor_update();
    return data;
}

// Retrieve 1-byte signed integer.
int8_t buffer::read_int8()
{
    return *static_cast<int8_t*>(read(1));
}

// Retrieve 1-byte unsigned integer.
uint8_t buffer::read_uint8()
{
    return *static_cast<uint8_t*>(read(1));
}

// Write raw data to buffer.
void buffer::write(void *data, size_t length)
{
    if ((m_length - m_cursor_pos) < length) {
        resize(m_cursor_pos + length);
    }
    memcpy(m_cursor_data, data, length);
    m_cursor_pos += length;
    cursor_update();
}
