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
}

// Destructor. @@@ What do?
socket::~socket()
{

}

// Establish a socket connection.
void socket::connect(const char *endpoint)
{
    debug("network", "Connecting to: ", false);
    debug("network", endpoint);
    if (zmq_connect(m_socket, endpoint) != 0) {
        throw exception::fatal(network::error());
    }
    debug("network", "Connection Established.");
}

// Establish a socket binding.
void socket::bind(const char *endpoint)
{
    debug("network", "Binding to: ", false);
    debug("network", endpoint);
    if (zmq_bind(m_socket, endpoint) != 0) {
        throw exception::fatal(network::error());
    }
    debug("network", "Binded and Listening.");
}

// Send a message over this socket.
bool socket::send(network::message *msg)
{
    void *data = 0;
    const void *temp_data = 0;
    size_t length = 0;
    int flags = 0;
    zmq_msg_t zm;

    // Check for empty message.
    if (msg == nullptr || !msg->more()) {
        return false;
    }

    // Send message part-by-part.
    while (msg->more()) {
        msg->get_next_part(temp_data, length);
        if (msg->more()) {
            flags = ZMQ_SNDMORE;
        } else {
            flags = 0;
        }

        // Extract data from Cosmodon message.
        data = malloc(length);
        memcpy(data, temp_data, length);

        // Move data into 0MQ message.
        if (zmq_msg_init_data(&zm, data, length, zfree, nullptr) == -1) {
            throw exception::fatal(network::error());
        }

        // Send part, check for failure.
        if (zmq_msg_send(&zm, m_socket, flags) == -1) {
            return false;
        }

        // Delete 0MQ message.
        zmq_msg_close(&zm);
    }
    return true;
}

// Receive a message over this socket.
bool socket::receive(network::message &msg)
{
    zmq_msg_t part;
    void *data;
    size_t length;
    int result;

    frame::FORMAT header_type;
    bool header = true, expecting = true;
    network::frame::base *temp_frame;

    bool garbage = false;

    // Prepare Cosmodon message.
    msg.clear();

    // Initialize 0MQ message.
    if (zmq_msg_init(&part) == -1) {
        throw exception::fatal(network::error());
    }
    
    // Receive any messages part-by-part.
    do {
        // Skip garbage message. @@@ Better method?
        if (garbage) {
            zmq_msg_recv(&part, m_socket, ZMQ_NOBLOCK);
        }

        // Check for data, and move data into 0MQ message.
        result = zmq_msg_recv(&part, m_socket, ZMQ_NOBLOCK);
        if (result == -1) {
            if (zmq_errno() != EAGAIN) {
                throw exception::fatal(network::error());
            }

            // No data available.
            return false;
        }
        
        // Check for empty message.
        else if (result == 0) {
            continue;
        }

        // Extract data from 0MQ message.
        data = zmq_msg_data(&part);
        length = zmq_msg_size(&part);

        // Check if data is available to process.
        if (length <= 0) {
            garbage = true;
            continue;
        }

        // Start new Cosmodon frame.
        if (header) {
            // Broken sequence.
            if (length != 1) {
                garbage = true;
                continue;
            }

            // Identify frame type.
            header_type = *reinterpret_cast<frame::FORMAT*>(data);
            if (header_type == frame::FORMAT::ACK) {
                temp_frame = new frame::ack; 
            }

            // Broken frame, perhaps broken sequence.
            else {
                garbage = true;
                continue;
            }

            // Add frame.
            msg.add(temp_frame);
        }

        // Move data into Cosmodon frame.
        else {
            temp_frame->set_next_part(data, length);
        }

        // Check if new frame should begin.
        if (temp_frame->more()) {
            header = false;
            expecting = true;
        } else {
            header = true;
            expecting = false;
        }
    } while (more_incoming());

    // Delete 0MQ message.
    zmq_msg_close(&part);

    // Return success or failure.
    if (garbage || expecting || msg.empty()) {
        msg.clear();
        return false;
    }
    return true;
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
