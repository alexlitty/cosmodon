#ifndef COSMODON_MODEL
#define COSMODON_MODEL

#include "vertex.hpp"
#include "window.hpp"

namespace cosmodon
{
    class model
    {
    protected:
        // Collection of vertices.
        std::vector<vertex> m_vertices;

    public:
        /**
         * Constructor.
         */
        model();

        /**
         * Render this model onto a window.
         *
         * Upon failure, a Fatal Cosmodon Exception is thrown.
         */
        void render(cosmodon::window &window);
    };
}

#endif
