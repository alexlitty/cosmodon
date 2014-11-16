#ifndef COSMODON_DEBUG
#define COSMODON_DEBUG

#include <iostream>

namespace cosmodon
{
    /**
     * Send a verbose status message to the console.
     *
     * Helpful for troubleshooting.
     */
    template <typename T>
    void debug(const char* category, T msg, bool done = true)
    {
        std::cout << "[" << category << "] ";
        std::cout << msg;
        if (done) {
            std::cout << std::endl;
        }
    }

    template <typename T>
    void debug(T msg, bool done = true)
    {
        std::cout << msg;
        if (done) {
            std::cout << std::endl;
        }
    }
}

#endif
