#include <network_message.hpp>
#include <debug.hpp>

using namespace cosmodon::network;

// Message constructor.
message::message() : m_frame_header(false), m_current_frame(0)
{

}

// Message destructor.
message::~message()
{
    for (unsigned char i = 0; i < m_frames.size(); i++) {
        delete m_frames[i];
    }
}

// Reset internal frame counter.
void message::reset()
{
    m_current_frame = 0;
    for (unsigned char i = 0; i < m_frames.size(); i++) {
        m_frames[i]->reset();
    }
    m_frame_header = false;
}

// Add a frame.
void message::add(frame::base* new_frame)
{
    m_frames.push_back(new_frame);
}

// Check whether there are more parts to input or output.
bool message::more()
{
    return (m_current_frame < m_frames.size());
}

// Retrieve the next frame. @@@ Not the best implementation.
void message::get_next_part(const void *&data, size_t &length)
{
    // Prevent out-of-range errors by looping around.
    if (!more()) {
        reset();
    }

    // Send the current frame header, if we haven't already.
    if (!m_frame_header) {
        m_frame_header = true;
        m_frames[m_current_frame]->get_header_part(data, length);
    }

    // Send the next part.
    else {
        m_frames[m_current_frame]->get_next_part(data, length);
    }

    // Determine the proceeding part.
    if (!m_frames[m_current_frame]->more()) {
        m_frames[m_current_frame]->reset();
        m_current_frame++;
        m_frame_header = false;
    }
}
