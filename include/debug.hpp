#ifndef COSMODON_DEBUG
#define COSMODON_DEBUG

#ifndef COSMODON_APP_NAME
#define COSMODON_APP_NAME "cosmodon"
#endif

#include <string>

namespace cosmodon
{
    /**
     * Send a verbose status message to the console.
     *
     * Helpful for troubleshooting.
     */
    void debug(const char* category, const char* msg, bool done = true);

    /**
     * Wrapper of the standard debug function, for standard strings.
     */
    void debug(const char* category, std::string msg, bool done = true);
}

#endif
