#ifndef COSMODON_PHYSICS_BOUNDARY
#define COSMODON_PHYSICS_BOUNDARY

namespace cosmodon
{
    /**
     * A boundary to pair with a model. Used to apply heuristics during intersection and collision logic.
     *
     * Since it is also a model, it can be manipulated and drawn as such.
     */
    class boundary : public model
    {
    public:

        /**
         * Determines if this boundary intersects with a model.
         *
         * @param  other  Model to compare against.
         *
         * @returns  True if an intersection exists, or false otherwise.
         */
        virtual bool intersects(const model &other) const = 0;

        /**
         * Determines if this boundary intersects with another boundary.
         *
         * @param  other  Boundary to compare against.
         *
         * @returns  True if an intersection exists, or false otherwise.
         */
        virtual bool intersects(const boundary &other) const = 0;
    };
}

#endif
