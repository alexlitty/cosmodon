#ifndef COSMODON_RENDER_OPENGL_HPP
#define COSMODON_RENDER_OPENGL_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>

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

        // Vector of internal window handles opened by this driver.
        GLFWwindow* m_handle;

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
        opengl(uint16_t width, uint16_t height, std::string title);

        /**
         * Destructor.
         */
        virtual ~opengl();

        /**
         * Clear rendering area using a color.
         */
        virtual void clear(color c = cosmodon::black) override;

        /**
         * Render a collection of vertices.
         */
        virtual void render(vertices *v) override;

        /**
         * Display rendered objects.
         */
        virtual void display() override;

        /**
         * Set shaders.
         */
        virtual bool set_shaders(shader *vertex = nullptr, shader *fragment = nullptr, shader *geometry = nullptr) override;
    };
}

#endif
