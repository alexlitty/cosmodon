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

        // Constructor.
        settings(irr::IrrlichtDevice *i = nullptr) : irrlicht(i) { }
    };
}

#endif
