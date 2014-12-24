#ifndef COSMODON_COMPONENT_CODE
#define COSMODON_COMPONENT_CODE

namespace cosmodon
{
    namespace component
    {
        /**
         * Programmable component.
         *
         * Used to give an object executable purpose.
         */
        class code
        {
        public:
            /**
             * Execute this object's program.
             *
             * Implemented by derived class.
             *
             * Returns true if the program requires further execution, or false if the program
             * is finished.
             */
            virtual bool execute() = 0;
        };
    }
}

#endif
