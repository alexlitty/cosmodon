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
     *
     * @@@ Implement graphic component.
     */
    class vertex : public point, public color
    {
    public:
        // Alpha.
        float a;

        /**
         * Constructor.
         */
        vertex(float init_x = 0, float init_y = 0, float init_z = 0, float init_a = 0);
    };

    /**
     * A collection of vertices to be rendered.
     */
    class vertices : public component::graphic
    {
    protected:
        // Internal vertex storage.
        std::vector<vertex> m_vertices;

        // Primitive explaining how vertices should be drawn.
        cosmodon::primitive m_primitive;

    public:
        /**
         * Constructor.
         */
        vertices(cosmodon::primitive primitive = cosmodon::primitive::triangle);

        /**
         * Destructor.
         */
        ~vertices();

        /**
         * Adds a vertex to the collection.
         */
        void add(const vertex& v);

        /**
         * Retrieves the amount of vertices inside this collection.
         */
        uint32_t size() const;
        
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

        /**
         * Data access operators.
         */
        vertex& operator [](const uint32_t index);
        const vertex& operator [](const uint32_t index) const;
    };
}

#endif
