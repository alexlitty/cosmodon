#ifndef COSMODON_LAYER
#define COSMODON_LAYER

#include "component/code.hpp"

namespace cosmodon
{
    /**
     * An execution layer, used alone or with others to run an application.
     *
     * Although a whole program can run in a single layer, layers intend to separate bigger
     * programs into tinier, controllable pieces of code.
     *
     * Derive and define virtual functions to implement a layer.
     */
    class layer : public component::code
    {
    public:
        /**
         * Constructor.
         *
         * Purposely empty.
         */
        layer();

        /**
         * Destructor.
         *
         * Purposely empty.
         */
        virtual ~layer();

        /**
         * Perform the layer program.
         *
         * The philosophy of Cosmodon is to return false when this layer has completed its program,
         * and return true when it needs additional execution. Upon returning false, the layer
         * should be discarded or prepared for another use.
         */
        virtual bool execute() = 0;
    };
}

#endif
