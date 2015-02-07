#ifndef COSMODON_RENDER_GRAPHIC_HPP
#define COSMODON_RENDER_GRAPHIC_HPP

#include "target.hpp"
#include "../transformation.hpp"
#include "../component/position.hpp"

/**
 * Forward declarations to resolve circular dependencies.
 */
namespace cosmodon
{
    namespace render
    {
        class target;
    }
}

/**
 * Normal declarations.
 */
namespace cosmodon
{
    /**
     * Base graphical object.
     *
     * Graphics are able to be rendered on a rendering target.
     */
    class graphic : public transformation, public component::position
    {
    public:
        /**
         * Renders this graphic onto a target.
         */
        virtual void render(render::target *target) = 0;
    };
}

#endif
