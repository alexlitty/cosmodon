#include <exception.hpp>

using namespace cosmodon;

// Base exception constructor.
exception::base::base(std::string message)
{
    m_message = message;
}

// Base exception deconstructor.
exception::base::~base() noexcept(true)
{

}

// Base exception message retriever.
const char* exception::base::what() const noexcept(true)
{
    return m_message.c_str();
}

// Fatal exception constructor.
exception::fatal::fatal(std::string message) : cosmodon::exception::base::base(message)
{

}

// Error exception constructor.
exception::error::error(std::string message) : cosmodon::exception::base::base(message)
{

}
