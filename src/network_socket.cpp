#include <network_socket.hpp>

using namespace cosmodon;
using namespace cosmodon::network;

// Constructor.
socket::socket(void *context, int type)
{
    if (context == nullptr) {
        throw exception::fatal("Initialized Network Socket on Empty Context");
    }

    // Initialize socket.
    m_socket = zmq_socket(context, type);
    if (m_socket == nullptr) {
        throw exception::fatal(network::error());
    }

    // Start bit count and bitrate calculations.
    m_bits = 0;
    m_bits_total = 0;
    m_timer = time(nullptr);
}

// Destructor. @@@ What do?
socket::~socket()
{

}

// Establish a socket connection.
void socket::connect(const char *endpoint)
{
    debug("network", "Connecting to: ", false);
    debug(std::string(endpoint));
    if (zmq_connect(m_socket, endpoint) != 0) {
        throw exception::fatal(network::error());
    }
    debug("network", "Connection Established.");
}

// Establish a socket binding.
void socket::bind(const char *endpoint)
{
    debug("network", "Binding to: ", false);
    debug(std::string(endpoint));
    if (zmq_bind(m_socket, endpoint) != 0) {
        throw exception::fatal(network::error());
    }
    debug("network", "Binded and Listening.");
}

// Send data to the network using a buffer.
void socket::send(network::buffer &x)
{
    size_t length = x.size();
    void *data;

    // Check for empty message.
    if (length == 0) {
        return;
    }

    // Retrieve entire raw buffer.
    data = x.read(length);
    if (zmq_send(m_socket, data, length, 0) == -1) {
        throw exception::fatal(network::error());
    }

    // Count bits up, clean up.
    tally(length);
    return;
}

// Receive data from the network into a buffer.
bool socket::receive(network::buffer &x)
{
    size_t length = 0;
    void *data = nullptr;
    int result;
    x.clear();

    // Attempt to receive data.
    result = zmq_recv(m_socket, data, length, ZMQ_NOBLOCK);

    // Check receive status.
    if (result == -1) {
        if (zmq_errno() != EAGAIN) {
            throw exception::fatal(network::error());
        }

        // No data available.
        return false;
    }

    // Check for empty message.
    if (result == 0) {
        return false;
    }

    // Load data into buffer.
    x.write(data, length);
    return true;
}

// Tally bits.
void socket::tally(unsigned int bits)
{
    m_bits_total += bits;
    m_bits += bits;
}

// Return total bits transferred.
std::string socket::transferred(bool bytes)
{
    return network::bits_readable(m_bits_total, bytes);
}

// Return recent bitrate. @@@ Could be better than seconds.
std::string socket::rate()
{
    // Calculate time passed.
    time_t passed = time(nullptr) - m_timer;
    if (passed == 0) {
        return "0 bps";
    }

    // Calculate bitrate.
    std::string bitrate = network::bits_readable((int) m_bits / passed);

    // Reset timer and recent bit counter.
    m_timer = time(nullptr);
    m_bits = 0;
    return bitrate + "ps";
}

// Retrieves a socket option.
void socket::get_opt(int option, int &value)
{
    static size_t length = sizeof(int);
    if (zmq_getsockopt(m_socket, option, &value, &length) == -1) {
        throw exception::fatal("Cannot retrieve socket option");
    }
}

// Check if more parts are available for receiving.
bool socket::more_incoming()
{
    int more;
    get_opt(ZMQ_RCVMORE, more);
    return (more == 1);
}

// Set outgoing high water mark.
void socket::set_send_hwm(unsigned int value)
{
    zmq_setsockopt(m_socket, ZMQ_SNDHWM, &value, sizeof value);
}

// Set incoming high water mark.
void socket::set_receive_hwm(unsigned int value)
{
    zmq_setsockopt(m_socket, ZMQ_RCVHWM, &value, sizeof value);
}

// Set subscription filter.
void socket::set_filter(const void *value)
{
    zmq_setsockopt(m_socket, ZMQ_SUBSCRIBE, value, sizeof value);
}

// Unset subscription filter.
void socket::unset_filter(const void *value)
{
    zmq_setsockopt(m_socket, ZMQ_UNSUBSCRIBE, value, sizeof value);
}

// Set identity.
void socket::set_identity(const void *value)
{
    zmq_setsockopt(m_socket, ZMQ_IDENTITY, value, sizeof value);
}

// Get identity.
void socket::get_identity(const void *value)
{
    zmq_setsockopt(m_socket, ZMQ_IDENTITY, value, sizeof value);
}

// Set lingering period.
void socket::set_linger(unsigned int value)
{
    zmq_setsockopt(m_socket, ZMQ_LINGER, &value, sizeof value);
}
