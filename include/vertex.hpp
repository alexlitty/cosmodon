#ifndef COSMODON_VERTEX
#define COSMODON_VERTEX

#include <vector>

#include "component/canvas.hpp"
#include "point.hpp"
#include "primitive.hpp"

namespace cosmodon
{
    /**
     * A vertex.
     *
     * Functionally identical to a point, but separated to add functionality.
     */
    class vertex : public point
    {
        // @@@ Derive as graphical component
    };

    /**
     * A collection of vertices to be rendered.
     */
    class vertices : public component::graphic
    {
    protected:
        // Programmer-friendly vertices container.
        std::vector<vertex> m_vertices;

        // GPU-friendly vertices container.
        const float *m_vertices_raw;

        // Primitive explaining how vertices should be drawn.
        cosmodon::primitive m_primitive;

    public:
        /**
         * Constructor.
         */
        vertices(cosmodon::primitive primitive = cosmodon::primitive::triangle);

        /**
         * Sets the primitive of vertices.
         */
        void set_primitive(cosmodon::primitive primitive);

        /**
         * Retrieves the primitive of vertices.
         */
        cosmodon::primitive get_primitive();

        /**
         * Render vertices to a canvas object.
         */
        void render(component::canvas *object);
    };
}

#endif
