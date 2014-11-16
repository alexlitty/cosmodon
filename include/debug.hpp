#ifndef COSMODON_DEBUG
#define COSMODON_DEBUG

#ifndef COSMODON_APP_NAME
#define COSMODON_APP_NAME "cosmodon"
#endif

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
        static bool preceded = false;

        // Send message header, if necessary, and message.
        if (!preceded) {
            std::cout << "[" << COSMODON_APP_NAME;
            std::cout << " / " << category;
            std::cout << "] ";
        }
        std::cout << msg;

        // Prepare next possible message.
        if (done) {
            std::cout << std::endl;
            preceded = false;
        } else {
            preceded = true;
        }
    }
}

#endif
