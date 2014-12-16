#ifndef COSMODON_ENGINE
#define COSMODON_ENGINE

#include "layer.hpp"
#include "exception.hpp"
#include "network_utility.hpp"

namespace cosmodon
{
    /**
     * The Central Class of Cosmodon Applications.
     *
     * Executes a given root layer.
     */
    class engine : public component::code
    {
    protected:
        // Root execution layer.
        layer *m_layer;

    public:
        /**
         * Constructor.
         */
        engine(layer *program = nullptr);

        /**
         * Destructor.
         */
        ~engine();

        /**
         * Perform engine execution.
         *
         * @@@ Currently takes control of program and always returns false. Change intended.
         */
        bool execute();

        /**
         * Sets the root layer, returning the old root.
         */
        layer* set_layer(layer *root);
    };
}

#endif
