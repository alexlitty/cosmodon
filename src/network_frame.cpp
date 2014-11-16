#include <network_frame.hpp>
#include <debug.hpp>

using namespace cosmodon::network;

/**
 * Base Frame.
 */
frame::base::base(frame::FORMAT format, unsigned char parts)
  : m_current(0), m_format(format), m_parts(parts)
{

}

// Basic frame destructor.
frame::base::~base()
{

}

// Reset the internal part counter.
void frame::base::reset()
{
    m_current = 0;
}

// Check if more parts are available for output or input.
bool frame::base::more()
{
    return (m_current < m_parts);
}

// Provides next available part.
void frame::base::get_next_part(const void *&data, size_t &length)
{
    if (!more()) {
        reset();
    }
    get_part(m_current++, data, length);
}

// Sets next available part.
bool frame::base::set_next_part(const void *data, size_t length)
{
    if (!more()) {
        reset();
    }
    return set_part(m_current++, data, length);
}

// Retrieves the header part of this frame.
void frame::base::get_header_part(const void *&data, size_t &length)
{
    data = &m_format;
    length = sizeof m_format;
}

/**
 * Acknowledgement Frame.
 */
frame::ack::ack(bool request_return)
  : base(FORMAT::ACK, 1), m_request_return(request_return)
{

}

// Provide a part.
void frame::ack::get_part(unsigned char index, const void *&data, size_t &length)
{
    data = &m_request_return;
    length = sizeof m_request_return;
}

// Set a part.
bool frame::ack::set_part(unsigned char index, const void *data, size_t length)
{
    if (length != sizeof m_request_return) {
        return false;
    }

    m_request_return = *static_cast<const bool*>(data);
    return true;
}

// Set request return.
void frame::ack::set_request_return(bool request_return)
{
    m_request_return = request_return;
}

// Get request return.
bool frame::ack::get_request_return()
{
    return m_request_return;
}
