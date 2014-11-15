#include <exception.hpp>

using namespace cosmodon;

// Base exception constructor.
exception::base::base(std::string message)
{
    m_message = message;
}

// Base exception deconstructor.
exception::base::~base() throw()
{

}

// Base exception message retriever.
std::string exception::base::what()
{
    return m_message;
}

// Fatal exception constructor.
exception::fatal::fatal(std::string message) : cosmodon::exception::base::base(message)
{

}

// Error exception constructor.
exception::error::error(std::string message) : cosmodon::exception::base::base(message)
{

}
