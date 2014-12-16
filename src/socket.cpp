#include <socket.hpp>

// Base socket constructor.
cosmodon::socket::base::base()
{
    m_bytes_out = 0;
    m_bytes_out_total = 0;

    m_bytes_in = 0;
    m_bytes_in_total = 0;
}

// Return bytes sent.
uint32_t cosmodon::socket::base::bytes_out()
{
    return 0;
}

// Return bytes received.
uint32_t cosmodon::socket::base::bytes_in()
{
    return 0;
}

// Return outgoing throughput.
uint32_t cosmodon::socket::base::rate_out()
{
    return 0;
}

// Return incoming throughput.
uint32_t cosmodon::socket::base::rate_in()
{
    return 0;
}

// UDP Constructor.
cosmodon::socket::udp::udp(uint16_t port, size_t buffer_length) : cosmodon::socket::base()
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
    if (::bind(m_socket, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == -1) {
        throw exception::fatal("Socket Binding Failed");
    }

    // Allocate a buffer to transfer data.
    m_buffer_length = buffer_length;
    m_buffer = malloc(buffer_length);
}

// UDP Destructor.
cosmodon::socket::udp::~udp()
{
    ::close(m_socket);
    free(m_buffer);
}

// Send over UDP socket.
bool cosmodon::socket::udp::send(std::string destination, cosmodon::buffer &x)
{
    sockaddr_in address;
    size_t length = x.size();
    int result;

    // Check for empty message.
    if (length == 0) {
        return true;
    }

    // Prepare destination address.
    address.sin_family = AF_INET;
    inet_pton(AF_INET, destination.c_str(), &(address.sin_addr));
    address.sin_port = m_port;

    // Send data from buffer.
    result = ::sendto(m_socket, x.get_data(), x.size(), 0, reinterpret_cast<sockaddr*>(&address), sizeof(address));
    if (result == -1) {
        // @@@
        throw exception::error("Could not send data.");
    }

    // Count bits up, clean up.
    x.reset();
    m_bytes_out += result;
    m_bytes_out_total += result;
    return true;
}

// Receive using UDP socket.
bool cosmodon::socket::udp::receive(std::string &source, cosmodon::buffer &x)
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
    
    // Check for error.
    if (result == -1) {
        // No data available.
        if (errno == EAGAIN) {
            return false;
        }

        // @@@
        throw exception::error("Could not receive data.");
    }

    // Load data into buffer.
    x.write(m_buffer, result);
    x.reset();
    m_bytes_in += result;
    m_bytes_in_total += result;
    return true;
}
