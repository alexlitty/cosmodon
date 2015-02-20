#ifndef COSMODON_MODEL_HPP
#define COSMODON_MODEL_HPP

#include "vertex.hpp"
#include "render/graphic.hpp"

namespace cosmodon
{
    /**
     * A transformable instance of vertices.
     */
    class model : public vertices, public graphic
    {
        // Fill mode.
        bool m_fill;

    public:
        /**
         * Gets position of model.
         *
         * @@@ For now, this is center.
         */
        virtual vector get_position() const override;

        /**
         * Gets center of model in absolute coordinates.
         */
        virtual vector get_center() const override;

        /**
         * Sets fill mode.
         */
        void set_fill(bool fill);

        /**
         * Checks if fill mode is enabled.
         */
        bool is_fill() const;

        /**
         * Render model.
         */
        virtual void render(render::target *object) const override;
    };
}

#endif
