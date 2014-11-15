#include <iostream>
#include <debug.hpp>

// Send a generic debug message.
void cosmodon::debug(const char* category, const char* msg, bool done)
{
    static bool preceded = false;

    // Send message header, if necessary, and message.
    if (!preceded) {
        std::cout << "[" << COSMODON_APP_NAME;
        std::cout << " * " << category;
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

// Debug message wrapper for strings.
void cosmodon::debug(const char* category, std::string msg, bool done)
{
    debug(category, msg.c_str(), done);
}
