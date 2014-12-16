#include <event.hpp>

// Constructor for event receiver.
cosmodon::event::receiver::receiver()
{
    for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++) {
        m_key_down[i] = false;
    }
}

// Interpretting an event.
bool cosmodon::event::receiver::OnEvent(const irr::SEvent& current_event)
{
    // Remember key press
    //if (current_event.EventType == irr::EET_KEY_INPUT_EVENT) {
    //    m_key_down[current_event.KeyInput.key] = current_event.KeyInputPressedDown;
    //}

    // Log Event
    if (current_event.EventType == irr::EET_LOG_TEXT_EVENT)
    {
        return true;
    }
    return false;
}

// Determine if key is pressed down.
bool cosmodon::event::receiver::IsKeyDown(irr::EKEY_CODE key) const
{
    return m_key_down[key];
}
