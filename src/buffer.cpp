#include <cstring>
#include <ios>
#include <sstream>
#include <buffer.hpp>

// Buffer constructor.
cosmodon::buffer::buffer(size_t new_length)
{
    if (new_length <= 0) {
        m_data = nullptr;
        m_length = 0;
    } else {
        m_data = malloc(new_length);
    }
    reset();

    // Set default write-mode.
    m_writing = true;
}

// Buffer copy constructor.
cosmodon::buffer::buffer(const buffer &other)
{
    m_writing = true;

    // Perform copy.
    write(other.m_data, other.m_length);
}

// Buffer destructor.
cosmodon::buffer::~buffer()
{
    clear();
}

// Updates cursor.
void cosmodon::buffer::cursor_update()
{
    if (m_data == nullptr) {
        m_cursor_pos = 0;
        m_cursor_data = nullptr;
    } else {
        m_cursor_data = static_cast<char*>(m_data) + m_cursor_pos;
    }
}

// Clear buffer.
void cosmodon::buffer::clear()
{
    free(m_data);
    m_data = nullptr;
    m_length = 0;
    reset();
}

// Resets cursor position.
void cosmodon::buffer::reset()
{
    m_cursor_pos = 0;
    m_cursor_data = m_data;
}

// Alias for reset.
void cosmodon::buffer::rewind()
{
    reset();
}

// Returns size of this buffer in bytes.
uint32_t cosmodon::buffer::size() const
{
    return m_length;
}

// Alias for size().
uint32_t cosmodon::buffer::length() const
{
    return m_length;
}

// Returns bytes remaining to be read or written.
uint32_t cosmodon::buffer::remaining() const
{
    return m_length - m_cursor_pos;
}

// Resize buffer.
void cosmodon::buffer::resize(size_t new_length)
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

// Retrieve read-only pointer to data.
const void* cosmodon::buffer::get_data(uint32_t amount)
{
    // Return all data.
    if (amount == 0) {
        return m_data;
    }

    // Ensure enough data remains.
    if (remaining() < amount) {
        throw cosmodon::exception::error("Buffer overflow");
    }

    // Update cursor, return requested data.
    m_cursor_pos += amount;
    cursor_update();
    return m_cursor_data;
}

// Retrieves raw data of given length.
bool cosmodon::buffer::read(void *&data, size_t length)
{
    data = nullptr;

    // Enforce read-mode.
    if (m_writing) {
        reset();
        m_writing = false;
    }

    // Check for overflow.
    if (remaining() < length) {
        throw cosmodon::exception::error("Buffer overflow");
    }

    // Copy data.
    data = malloc(length);
    memcpy(data, m_cursor_data, length);

    // Update cursor, clean up.
    m_cursor_pos += length;
    cursor_update();
    return true;
}

// Retrieve data as a string.
bool cosmodon::buffer::read(std::string &data)
{
    uint8_t size;

    read(size);
    data.clear();
    data.assign(reinterpret_cast<const char*>(get_data(size)), static_cast<size_t>(size));
    return true;
}

// Write raw data to buffer.
bool cosmodon::buffer::write(const void *data, size_t length)
{
    // Enforce write-mode.
    if (!m_writing) {
        reset();
        m_writing = true;
    }

    // Resize buffer to accommodate new data.
    if ((m_length - m_cursor_pos) < length) {
        resize(m_cursor_pos + length);
    }

    // Copy data into buffer.
    memcpy(m_cursor_data, data, length);

    // Update cursor.
    m_cursor_pos += length;
    cursor_update();
    return true;
}

// Write a string to the buffer, up to 256 characters.
bool cosmodon::buffer::write(const std::string &data)
{
    uint8_t size = data.size();

    write(size);
    write(data.c_str(), size);
    return true;
}

// Dump buffer data.
std::string cosmodon::buffer::dump() const
{
    std::stringstream ss;
    for (uint32_t i = 0; i < length(); i++) {
        ss << std::hex << static_cast<uint8_t*>(m_data)[i];
    }
    return ss.str();
}

// Equivalent Operator.
bool cosmodon::buffer::operator==(const buffer &other)
{
    // Check size.
    if (size() != other.size()) {
        return false;
    }

    // Compare bytes.
    return (memcmp(m_data, other.m_data, size()) == 0);
}

// Inequivalent Operator.
bool cosmodon::buffer::operator!=(const buffer &other)
{
    return !(*this == other);
}
