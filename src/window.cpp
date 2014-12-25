#include <exception.hpp>
#include <window.hpp>

// @@@
#include <unistd.h>

// Local callback function to handle GLFW errors, and throw them into a Cosmodon exception.
static void handle_glfw_error(int error, const char* description)
{
    throw cosmodon::exception::fatal(std::string("OpenGL Error: ") + std::string(description));
}

// Constructor.
cosmodon::window::window()
{
    // Prepare GLFW error callback.
    glfwSetErrorCallback(handle_glfw_error);

    // Initialize GLFW.
    ::glfwInit();

    // Prepare window hints.
    ::glfwWindowHint(GLFW_SAMPLES, 4);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    ::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window.
    m_handle = ::glfwCreateWindow(1024, 768, "Cosmodon", nullptr, nullptr);
    ::glfwMakeContextCurrent(m_handle);

    // Initialize GLEW.
    glewExperimental = true;
    if (::glewInit() != GLEW_OK) {
        throw cosmodon::exception::fatal("Could not initialize GLEW.");
    }

    // Prepare OpenGL buffer.
    ::glGenBuffers(1, &m_buffer_positions);
    ::glGenBuffers(1, &m_buffer_colors);

    // Apply default shaders.
    cosmodon::shader vertex(cosmodon::shader::vertex), fragment(cosmodon::shader::fragment);
    apply(&vertex);
    apply(&fragment);
}

// Destructor.
cosmodon::window::~window()
{
    ::glDeleteBuffers(1, &m_buffer_positions);
    ::glDeleteBuffers(1, &m_buffer_colors);
    ::glfwDestroyWindow(m_handle);
    ::glfwTerminate();
}

// Apply shader.
void cosmodon::window::apply(cosmodon::shader *shader, bool link)
{
    GLint status;
    GLuint shader_object;
    GLenum shader_type;
    const char *shader_code = shader->code.c_str();

    // Determine shader type.
    if (shader->level == cosmodon::shader::vertex) {
        shader_type = GL_VERTEX_SHADER;
    } else if (shader->level == cosmodon::shader::fragment) {
        shader_type = GL_FRAGMENT_SHADER;
    } else {
        throw cosmodon::exception::fatal("Cannot apply shader with unsupported level.");
    }

    // Compile shader with given code.
    shader_object = glCreateShader(shader_type);
    glShaderSource(shader_object, 1, &shader_code, nullptr);
    glCompileShader(shader_object);

    // Check compilation for errors.
    glGetShaderiv(shader_object, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        std::string report_final;
        GLchar *report;
        GLint report_length;

        // Retrieve report.
        ::glGetShaderiv(shader_object, GL_INFO_LOG_LENGTH, &report_length);
        report = new GLchar[report_length + 1];
        ::glGetShaderInfoLog(shader_object, report_length, nullptr, report);
        report_final = report;
        delete [] report;

        // Throw exception.
        throw cosmodon::exception::fatal(std::string("Shader compilation failed: \n\n") + report_final);
    }

    // Couple shader to window.
    if (shader_type == GL_VERTEX_SHADER) {
        m_shader_vertex = shader_object;
    } else {
        m_shader_fragment = shader_object;
    }

    // Link shaders into a program, if requested.
    if (link) {
        glUseProgram(0);
        glDeleteProgram(m_shader_program);
        m_shader_program = glCreateProgram();

        // Attempt the link.
        glAttachShader(m_shader_program, m_shader_vertex);
        glAttachShader(m_shader_program, m_shader_fragment);
        glLinkProgram(m_shader_program);
        glGetProgramiv(m_shader_program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            throw cosmodon::exception::fatal("Shader linking failed.");
        }

        // Free vertex shader.
        glDetachShader(m_shader_program, m_shader_vertex);
        glDeleteShader(m_shader_vertex);
        m_shader_vertex = 0;

        // Free fragment shader.
        glDetachShader(m_shader_program, m_shader_fragment);
        glDeleteShader(m_shader_fragment);
        m_shader_fragment = 0;

        // Start using linked program.
        glUseProgram(m_shader_program);
    }
}

// Clear the window using a color.
void cosmodon::window::clear(cosmodon::color &color)
{
    ::glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
    ::glClear(GL_COLOR_BUFFER_BIT);
}

// Render vertices to the window.
void cosmodon::window::render(cosmodon::vertices &vertices)
{
    static float *vertex_positions;
    static float *vertex_colors;

    // Get vertex positions.
    vertex_positions = new float[vertices.size() * 4];
    for (uint32_t i = 0; i < vertices.size(); i++) {
        vertex_positions[i + 0] = vertices[i].x;
        vertex_positions[i + 1] = vertices[i].y;
        vertex_positions[i + 2] = vertices[i].z;
        vertex_positions[i + 3] = 1.0f;
    }

    // Get vertex colors.
    vertex_colors = new float[vertices.size() * 3];
    for (uint32_t i = 0; i < vertices.size(); i++) {
        vertex_colors[i + 0] = vertices[i].b;
        vertex_colors[i + 1] = vertices[i].g;
        vertex_colors[i + 2] = vertices[i].r;
    }

    // Load positions into GPU buffer.
    ::glBindBuffer(GL_ARRAY_BUFFER, m_buffer_positions);
    ::glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, vertex_positions, GL_STATIC_DRAW);
    ::glEnableVertexAttribArray(0);
    ::glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // Load colors into GPU buffer.
    ::glBindBuffer(GL_ARRAY_BUFFER, m_buffer_colors);
    ::glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3, vertex_colors, GL_STATIC_DRAW);
    ::glEnableVertexAttribArray(1);
    ::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Render.
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    // Unbind resources.
    delete [] vertex_positions;
    delete [] vertex_colors;
    ::glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Display currently rendered graphics on the window.
void cosmodon::window::display()
{
    // Calculate FPS.
    m_fps.tally();

    // Display graphics.
    ::glfwSwapBuffers(m_handle);
}

// Retrieve current FPS.
uint16_t cosmodon::window::fps() const
{
    return m_fps.get();
}
