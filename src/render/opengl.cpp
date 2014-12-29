#include <exception.hpp>
#include <render/opengl.hpp>

// Set total running OpenGL instances.
uint8_t cosmodon::opengl::m_instances = 0;

// Local callback function to handle GLFW errors.
static void handle_glfw_error(int error, const char *description)
{
    throw cosmodon::exception::fatal(std::string("OpenGL Error: ") + std::string(description));
}

// Constructor.
cosmodon::opengl::opengl(uint16_t width, uint16_t height, std::string title)
{
    // Ensure this is the only active instance. @@@ Change later.
    if (m_instances != 0) {
        throw cosmodon::exception::fatal("Failed to initialize OpenGL: An instance already exists.");
    }
    m_instances++;

    // Initialize GLFW.
    ::glfwSetErrorCallback(handle_glfw_error);
    ::glfwInit();

    // Prepare new window hints.
    ::glfwWindowHint(GLFW_SAMPLES, 4);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    ::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window.
    m_handle = ::glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    ::glfwMakeContextCurrent(m_handle);

    // Initialize GLEW.
    ::glewExperimental = true;
    if (::glewInit() != GLEW_OK) {
        throw cosmodon::exception::fatal("Failed to initialize GLEW.");
    }

    // Generate OpenGL buffers.
    ::glGenBuffers(1, &m_positions);
    ::glGenBuffers(1, &m_colors);

    // Generate OpenGL vertex array objects.
    ::glGenVertexArrays(1, &m_array);
}

// Destructor.
cosmodon::opengl::~opengl()
{
    // Destroy OpenGL buffers.
    ::glDeleteBuffers(1, &m_positions);
    ::glDeleteBuffers(1, &m_positions);

    // Deinitialize GLFW.
    ::glfwTerminate();

    // Reset instance count.
    m_instances--;
}

// Clear rendering area using a color.
void cosmodon::opengl::clear(cosmodon::color color)
{
    ::glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
    ::glClear(GL_COLOR_BUFFER_BIT);
}

#include <iostream>

// Render vertices.
void cosmodon::opengl::render(cosmodon::vertices *v)
{
    uint32_t i, j;
    GLfloat *positions;
    GLfloat *colors;
    cosmodon::vertices vertices = *v;

    // Prepare vertices information.
    uint32_t count = vertices.size() * 4;

    // Bind vertex array.
    ::glBindVertexArray(m_array);

    // Get vertex positions.
    positions = new GLfloat[count];
    for (i = j = 0; i < vertices.size(); i++) {
        positions[j++] = vertices[i].x;
        positions[j++] = vertices[i].y;
        positions[j++] = vertices[i].z;
        positions[j++] = 1.0f;
    }

    // Point to vertex positions.
    ::glBindBuffer(GL_ARRAY_BUFFER, m_positions);
    ::glBufferData(GL_ARRAY_BUFFER, count*sizeof(GLfloat), positions, GL_DYNAMIC_DRAW);
    ::glEnableVertexAttribArray(0);
    ::glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // Get vertex colors.
    colors = new GLfloat[count];
    for (i = j = 0; i < vertices.size(); i++) {
        colors[j++] = vertices[i].r / 255.0f;
        colors[j++] = vertices[i].g / 255.0f;
        colors[j++] = vertices[i].b / 255.0f;
        colors[j++] = 255.0f / 255.0f;
    }

    // Point to vertex colors.
    ::glBindBuffer(GL_ARRAY_BUFFER, m_colors);
    ::glBufferData(GL_ARRAY_BUFFER, count*sizeof(GLfloat), colors, GL_DYNAMIC_DRAW);
    ::glEnableVertexAttribArray(1);
    ::glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // Render.
    ::glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    
    // Clean up.
    delete [] positions;
    delete [] colors;
    ::glDisableVertexAttribArray(0);
    ::glDisableVertexAttribArray(1);
}

// Display rendering area.
void cosmodon::opengl::display()
{
    ::glfwSwapBuffers(m_handle);

    // Tally frame towards FPS.
    m_fps.tally();
}

// Compile shader.
GLuint cosmodon::opengl::compile_shader(cosmodon::shader *shader)
{
    GLint status;
    GLuint type;
    GLuint object;
    const char *code = shader->code.c_str();

    // Determine shader type.
    switch (shader->level) {
        case cosmodon::shader::vertex:
            type = GL_VERTEX_SHADER;
            break;
        case cosmodon::shader::fragment:
            type = GL_FRAGMENT_SHADER;
            break;
        default:
            throw cosmodon::exception::fatal("Cannot compile OpenGL shader with unsupported type.");
            break;
    }

    // Compile shader.
    object = ::glCreateShader(type);
    ::glShaderSource(object, 1, &code, nullptr);
    ::glCompileShader(object);
    ::glGetShaderiv(object, GL_COMPILE_STATUS, &status);

    // Report compilation errors.
    if (status == GL_FALSE) {
        GLchar *report;
        GLint report_length;
        std::string msg;

        // Retrieve error information.
        ::glGetShaderiv(object, GL_INFO_LOG_LENGTH, &report_length);
        report = new GLchar[report_length + 1];
        ::glGetShaderInfoLog(object, report_length, nullptr, report);

        // Prepare exception message.
        msg = report;
        delete [] report;

        // Throw exception.
        ::glDeleteShader(object);
        throw cosmodon::exception::fatal(std::string("Failed to compile OpenGL shader: ") + msg);
    }

    // Return compiled OpenGL shader.
    return object;
}

// Set shaders.
bool cosmodon::opengl::set_shaders(cosmodon::shader *vertex, cosmodon::shader *fragment, cosmodon::shader *geometry)
{
    GLint status;
    GLuint shader_vertex;
    GLuint shader_fragment;

    // Destroy old program.
    ::glUseProgram(0);
    ::glDeleteProgram(m_shader_program);
    m_shader_program = ::glCreateProgram();

    // Bind attribute locations.
    ::glBindAttribLocation(m_shader_program, 0, "position");
    ::glBindAttribLocation(m_shader_program, 1, "color");

    // Compile shaders.
    shader_vertex = compile_shader(vertex);
    shader_fragment = compile_shader(fragment);

    // Link shaders.
    ::glAttachShader(m_shader_program, shader_vertex);
    ::glAttachShader(m_shader_program, shader_fragment);
    ::glLinkProgram(m_shader_program);
    ::glGetProgramiv(m_shader_program, GL_LINK_STATUS, &status);

    // Destroy shaders.
    ::glDetachShader(m_shader_program, shader_vertex);
    ::glDetachShader(m_shader_program, shader_fragment);
    ::glDeleteShader(shader_vertex);
    ::glDeleteShader(shader_fragment);

    // Report linking errors.
    if (status == GL_FALSE) {
        m_shader_program = 0;
        throw cosmodon::exception::fatal("Failed to link OpenGL shaders.");
        // @@@ return false;
    }

    // Start using new shader program.
    ::glUseProgram(m_shader_program);
    return true;
}

// Set window title.
void cosmodon::opengl::set_window_title(std::string title)
{
    ::glfwSetWindowTitle(m_handle, title.c_str());
}
