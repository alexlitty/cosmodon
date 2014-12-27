#ifndef COSMODON_RENDER_OPENGL_HPP
#define COSMODON_RENDER_OPENGL_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../render.hpp"

namespace cosmodon
{
    /**
     * A rendering interface to OpenGL.
     */
    class opengl : public render::driver
    {
    protected:
        // Total running OpenGL instances.
        static uint8_t m_instances;

        // Buffer for vertex positions.
        GLuint m_positions;

        // Buffer for vertex colors.
        GLuint m_colors;

        // Shader program.
        GLuint m_shader_program;

        /**
         * Compiles a shader.
         *
         * Returns an OpenGL shader object, which should be destroyed when no longer needed.
         */
        GLuint compile_shader(cosmodon::shader *shader);

    public:
        /**
         * Constructor.
         */
        opengl();

        /**
         * Destructor.
         */
        ~opengl();

        /**
         * Create a window.
         */
        virtual window* create_window(std::string title, uint16_t width, uint16_t height) override;

        /**
         * Render a collection of vertices.
         */
        virtual void render(vertices *v) override;

        /**
         * Set shaders.
         */
        virtual bool set_shaders(shader *vertex = nullptr, shader *fragment = nullptr, shader *geometry = nullptr) override;
    };
}

#endif
