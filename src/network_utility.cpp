#include <network_utility.hpp>
#include "utility.hpp"

using namespace cosmodon;
using namespace cosmodon::utility;

// Variety of ports.
const char* network::PORT::INTERNAL = "6700";
const char* network::PORT::EXTERNAL = "6708";

// Function used by 0MQ to free message memory.
void network::zfree(void *data, void *hint)
{
    free(data);
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
    return (std::string("zmq error: ") + std::string(zmq_strerror(zmq_errno()))).c_str();
}

// Returns a readable version of bits.
std::string network::bits_readable(unsigned int count, bool bytes)
{
    unsigned int x = (bytes ? count / 8 : count);
    std::string s;
    if (x < 1000) {
        s = to_string(x);
    } else if (x < 1000000) {
        s = to_string((int) x / 1000) + "K";
    } else if (x < 1000000000) {
        s = to_string((int) x / 1000000) + "M";
    } else if (x < 1000000000000) {
        s = to_string((int) x / 1000000000) + "G";
    } else {
        s = to_string((int) x / 1000000000000) + "T";
    }

    s += (bytes ? "B" : "b");
    return s;
}
