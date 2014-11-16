#include <network_utility.hpp>

using namespace cosmodon;

// Variety of ports.
const char* network::port::internal = "6700";
const char* network::port::external = "6708";

// Initializes a network context.
void* network::initialize()
{
    void *temp = zmq_ctx_new();
    if (temp == nullptr) {
        throw exception::fatal(network::error());
    }
    return temp;
}

// Easy endpoint formatting function.
const char* network::endpoint(const char* address, const char* port, const char* method)
{
    return (
        std::string(method) + std::string("://")
        + std::string(address) + std::string(":")
        + std::string(port)
    ).c_str();
}

// Returns current ZMQ error as string.
const char* network::error()
{
    return zmq_strerror(zmq_errno());
}
