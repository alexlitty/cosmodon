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
        // w component.
        cosmodon::number w;

        /**
         * Default constructor.
         */
        vertex();

        /**
         * Constructor, without w component.
         */
        vertex(number init_x, number init_y, number init_z, cosmodon::color c = cosmodon::black);

        /**
         * Constructor, with w component.
         */
        vertex(number init_x, number init_y, number init_z, number init_w,
          cosmodon::color c = cosmodon::black
        );

        /**
         * Constructor, from vector.
         */
        vertex(const vector &other, cosmodon::color c = cosmodon::black);

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
    class vertices
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
         * Clears this collection of all vertices.
         */
        void clear();

        /**
         * Adds a vertex to the collection.
         */
        void add(const vertex& v, bool end = true);

        /**
         * Retrieves center vertex.
         */
        virtual vector get_center() const;

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
         * Data access operators.
         */
        vertex& operator [](const uint32_t index);
        const vertex& operator [](const uint32_t index) const;
    };
}

// Vertex and matrix multiplication.
cosmodon::vertex operator*(const cosmodon::matrix &lhs, const cosmodon::vertex &rhs);
cosmodon::vertex operator*(const cosmodon::vertex &lhs, const cosmodon::matrix &rhs);

#endif
