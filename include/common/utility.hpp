#ifndef COSMODON_UTILITY
#define COSMODON_UTILITY

#include <sstream>
#include <string>

namespace cosmodon
{
    namespace utility
    {
        template <typename T>
        std::string to_string(const T &value)
        {
            std::stringstream oss;
            oss << value;
            return oss.str();
        }
    }
}

#endif
