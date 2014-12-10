#include <network_utility.hpp>
#include "utility.hpp"

using namespace cosmodon;
using namespace cosmodon::utility;

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
