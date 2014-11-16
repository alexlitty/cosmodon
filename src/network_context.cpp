#include <network_context.hpp>

using namespace cosmodon::network;

// Context constructor.
context::context()
{
    m_zmq_context = zmq_ctx_new();
    if (m_zmq_context == nullptr) {
        throw exception::fatal(network::error());
    }
}

// Context destructor. @@@ What do?
context::~context()
{
    
}

// Create socket on this context.
socket* context::create(int type)
{
    return new socket(m_zmq_context, type);
}
