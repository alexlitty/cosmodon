#include <network_utility.hpp>

using namespace cosmodon;

// Variety of ports.
const char* network::PORT::INTERNAL = "6700";
const char* network::PORT::EXTERNAL = "6708";

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
    return (std::string("zmq error: ") + std::string(zmq_strerror(zmq_errno()))).c_str();
}
