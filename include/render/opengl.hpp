#ifndef COSMODON_RENDER_OPENGL_HPP
#define COSMODON_RENDER_OPENGL_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../render.hpp"
#include "../camera.hpp"

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

        // Vertex array objects.
        GLuint m_array;

        // Shader program.
        GLuint m_shader_program;

        // Width and height of the rendering viewport.
        uint16_t m_width;
        uint16_t m_height;

        // Current rendering camera.
        const camera *m_camera;

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
         * Set the camera.
         */
        virtual void set_camera(const camera &object);

        /**
         * Clear rendering area using a color.
         */
        virtual void clear(const color c = cosmodon::black) override;

        /**
         * Inherit all rendering methods.
         */
        using render::target::render;

        /**
         * Render a collection of vertices.
         */
        virtual void render(const vertices *v, const matrix &transform) override;

        /**
         * Sets view transformation.
         */
        void set_view(const transformation view);

        /**
         * Display the currently rendered result.
         */
        virtual void display() override;

        /**
         * Sets shaders.
         */
        virtual bool set_shaders(shader *vertex = nullptr, shader *fragment = nullptr, shader *geometry = nullptr) override;

        /**
         * Set window title.
         */
        void set_window_title(const std::string title);
    };
}

#endif
