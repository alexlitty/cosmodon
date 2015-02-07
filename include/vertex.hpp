#ifndef COSMODON_VERTEX
#define COSMODON_VERTEX

#include <vector>
#include <string>
#include <ostream>

#include "color.hpp"
#include "render/target.hpp"
#include "primitive.hpp"
#include "vector.hpp"

namespace cosmodon
{
    /**
     * A vertex.
     *
     * Functionally identical to a point, but separated to add functionality.
     *
     * @@@ Implement graphic component.
     */
    class vertex : public vector, public color
    {
    public:
        /**
         * Constructor.
         */
        vertex(float init_x = 0, float init_y = 0, float init_z = 0, cosmodon::color c = cosmodon::black);

        /**
         * Copy constructor.
         */
        vertex(const vertex &copy);

        /**
         * Convert to string, to visually explain its internal coordinates.
         */
        operator std::string() const;
    };

    /**
     * A collection of vertices to be rendered.
     */
    class vertices : public graphic
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
        void add(const vertex& v, bool end = true);

        /**
         * Recalculates information about this set of vertices.
         */
        void refresh();

        /**
         * Retrieves the vertex count of this collection.
         */
        uint32_t size() const;

        /**
         * Changes the vertex count inside this collection.
         */
        void resize(uint32_t amount);
        
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
        void render(render::target *target);

        /**
         * Data access operators.
         */
        vertex& operator [](const uint32_t index);
        const vertex& operator [](const uint32_t index) const;
    };
}

#endif
