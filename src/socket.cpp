#include <socket.hpp>

// @@@
#include <iostream>

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
    m_address_info = nullptr;
    sockaddr_in address;

    // Clear address info.
    ::memset(&m_address_info, 0, sizeof(m_address_info));
    
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
    ::freeaddrinfo(m_address_info);
    ::close(m_socket);
    free(m_buffer);
}

// Retrieve address information for an internal Unix socket. @@@ Multiple choices? Performance issues? Memory leak in address.
const addrinfo* cosmodon::socket::udp::get_address_info(std::string address)
{
    addrinfo *addr, hints;

    // Free old address information.
    ::freeaddrinfo(m_address_info);
    m_address_info = nullptr;

    // Prepare address hints.
    ::memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    // Retrieve address information.
    if (::getaddrinfo(address.c_str(), std::to_string(m_port).c_str(), &hints, &addr) != 0) {
        throw cosmodon::exception::fatal("Could not retrieve address information for UDP socket.");
    }
    m_address_info = addr;

    // Sanity check.
    char* dummy = static_cast<char*>(malloc(1024));
    inet_ntop(AF_INET, &((reinterpret_cast<sockaddr_in*>(m_address_info->ai_addr))->sin_addr), dummy, 1024);
    if (::strcmp(dummy, address.c_str()) != 0) {
        throw cosmodon::exception::fatal(std::string("Socket inaccurately converted address to binary: ") + std::string(dummy) + std::string(" != ") + address);
    }
    free(dummy);

    return m_address_info;
}

// Send over UDP socket.
bool cosmodon::socket::udp::send(cosmodon::buffer &x, std::string destination)
{
    const addrinfo* info;
    size_t length = x.size();
    int result;

    //std::cout << "((Sending!))" << std::endl;

    // Check for empty message.
    if (length == 0) {
        return true;
    }

    // Resolve destination address.
    info = get_address_info(destination);

    // Send data from buffer.
    result = ::sendto(m_socket, x.get_data(), x.size(), 0, info->ai_addr, info->ai_addrlen);
    if (result == -1) {
        throw exception::error("Could not send data.");
    }

    // Count bits up, clean up.
    x.reset();
    m_bytes_out += result;
    m_bytes_out_total += result;
    return true;
}

// Receive using UDP socket.
bool cosmodon::socket::udp::receive(cosmodon::buffer &x, std::string &source)
{
    sockaddr_storage address;
    socklen_t address_size = sizeof(address);
    char s[INET_ADDRSTRLEN];
    int result;
    x.clear();

    // Prepare to receive source address.
    address.ss_family = AF_INET;

    // Attempt to receive data.
    result = ::recvfrom(m_socket, m_buffer, m_buffer_length - 1, 0, reinterpret_cast<sockaddr*>(&address), &address_size);

    // Check for error.
    if (result == -1) {
        // No data available.
        if (errno == EAGAIN) {
            return false;
        }

        // @@@
        throw exception::error("Could not receive data.");
    }

    // Interpret address information.
    source = inet_ntop(address.ss_family, &address, s, sizeof(s)); 

    // Load data into buffer.
    x.write(m_buffer, result);
    x.reset();
    m_bytes_in += result;
    m_bytes_in_total += result;
    return true;
}
