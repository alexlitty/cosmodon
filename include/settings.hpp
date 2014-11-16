#ifndef COSMODON_SETTINGS
#define COSMODON_SETTINGS

#include "network_context.hpp"

namespace cosmodon
{
    /**
     * Stores information about a Cosmodon system and its layers.
     *
     * Used to pass engine information easily.
     */
    struct settings
    {
        irr::IrrlichtDevice *irrlicht;
        network::context *network_context;

        // Constructor.
        settings(irr::IrrlichtDevice *i = nullptr, network::context *ctx = nullptr) : irrlicht(i), network_context(ctx) { }
    };
}

#endif
