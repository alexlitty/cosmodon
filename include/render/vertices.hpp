#ifndef COSMODON_RENDER_VERTICES_HPP
#define COSMODON_RENDER_VERTICES_HPP

#include "vertex.hpp"
#include "primitive.hpp"
#include "transformation.hpp"

namespace cosmodon
{
    /**
     * A collection of vertices to be rendered.
     */
    class vertices : public transformation
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
         *
         * @param 
         */
        void add(number init_x, number init_y, number init_z);

        /**
         * Adds a vertex to the collection.
         *
         * @param  vert  Vertex to add.
         */
        void add(const vertex& vert);

        /**
         * Adds a set of vertices to the collection.
         */
        void add(const vertices& verts);

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

#endif
