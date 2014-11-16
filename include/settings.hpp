#ifndef COSMODON_SETTINGS
#define COSMODON_SETTINGS

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
        void *network_context;

        // Constructor.
        settings(irr::IrrlichtDevice *i = nullptr, void *ctx = nullptr) : irrlicht(i), network_context(ctx) { }
    };
}

#endif
