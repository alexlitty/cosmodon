#include <network_socket.hpp>

using namespace cosmodon;
using namespace cosmodon::network;

// Base socket constructor.
socket::base::base()
{
    m_bytes_out = 0;
    m_bytes_out_total = 0;

    m_bytes_in = 0;
    m_bytes_in_total = 0;
}

// Return bytes sent.
uint32_t socket::base::bytes_out()
{
    return 0;
}

// Return bytes received.
uint32_t socket::base::bytes_in()
{
    return 0;
}

// Return outgoing throughput.
uint32_t socket::base::rate_out()
{
    return 0;
}

// Return incoming throughput.
uint32_t socket::base::rate_in()
{
    return 0;
}

// UDP Constructor.
socket::udp::udp(uint16_t port) : socket::base()
{
    m_port = port;
    sockaddr_in address;
    
    // Initialize internal socket.
    m_socket = ::socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    if (m_socket == -1) {
        throw exception::fatal("Socket Initialization Failed");
    }

    // Prepare binding address.
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = m_port;

    // Bind socket.
    ::bind(m_socket, reinterpret_cast<sockaddr*>(&address), sizeof(address));
}

// UDP Destructor.
socket::udp::~udp()
{
    ::close(m_socket);
}

// Send over UDP socket.
bool socket::udp::send(network::buffer &x, std::string destination)
{
    sockaddr_in address;
    size_t length = x.size();

    // Check for empty message.
    if (length == 0) {
        return true;
    }

    // Prepare destination address.
    address.sin_family = AF_INET;
    inet_pton(AF_INET, destination.c_str(), &(address.sin_addr));
    address.sin_port = m_port;

    // Send data from buffer.
    m_buffer = x.read_raw(length);
    if (::sendto(m_socket, m_buffer, length, 0, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == -1) {
        // @@@
        throw exception::error("Could not send data.");
    }

    // Count bits up, clean up.
    x.reset();
    m_bytes_out += length;
    m_bytes_out_total += length;
    return true;
}

// Receive using UDP socket.
bool socket::udp::receive(network::buffer &x, std::string &source)
{
    sockaddr_storage address;
    socklen_t address_size = sizeof(address);
    int result;
    x.clear();

    // Prepare to receive source address.
    address.ss_family = AF_INET;

    // Attempt to receive data.
    result = ::recvfrom(m_socket, m_buffer, m_buffer_length, 0,
      reinterpret_cast<sockaddr*>(&address), &address_size);
    if (result == -1) {
        // @@@
        throw exception::error("Could not receive data.");
    }

    // Check for empty message.
    if (result == 0) {
        return false;
    }

    // Load data into buffer.
    x.write(m_buffer, result);
    x.reset();
    m_bytes_in += result;
    m_bytes_in_total += result;
    return true;
}
