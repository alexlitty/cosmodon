#ifndef COSMODON_EVENT
#define COSMODON_EVENT

#include "irrlicht/irrlicht.h"

namespace cosmodon
{
    namespace event
    {
        class receiver : public irr::IEventReceiver
        {
        protected:
            bool m_key_down[irr::KEY_KEY_CODES_COUNT];
        
        public:
            // Constructor
            receiver();

            // Interpretting an event
            virtual bool OnEvent(const irr::SEvent& current_event);

            // Determine if key is pressed down
            virtual bool IsKeyDown(irr::EKEY_CODE key) const;
        };
    }
}

#endif
