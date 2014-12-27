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
cosmodon::opengl::opengl()
{
    // Ensure this is the only active instance. @@@ Change later.
    if (m_instances != 0) {
        throw cosmodon::exception::fatal("Cannot initialize OpenGL in Cosmodon: An instance already exists.");
    }
    m_instances++;

    // Initialize GLFW.
    ::glfwSetErrorCallback(handle_glfw_error);
    ::glfwInit();

    // Initialize GLEW.
    ::glewExperimental = true;
    if (::glewInit() != GLEW_OK) {
        throw cosmodon::exception::fatal("Cannot initialize GLEW.");
    }

    // Generate OpenGL buffers.
    ::glGenBuffers(1, &m_positions);
    ::glGenBuffers(1, &m_colors);
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

// Create window.
cosmodon::window* cosmodon::opengl::create_window(std::string title, uint16_t width, uint16_t height)
{
    GLFWwindow *handle;
    cosmodon::window *window;

    // Prepare new window hints.
    ::glfwWindowHint(GLFW_SAMPLES, 4);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    ::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    ::glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window.
    handle = ::glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    window = new cosmodon::window(this, handle);

    // @@@ Will be problematic when implementing multiple windows.
    ::glfwMakeContextCurrent(handle);
    return window;
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

    // Bind vertex arrays to program.
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

// Render vertices.
void cosmodon::opengl::render(cosmodon::vertices *v)
{
    cosmodon::vertices vertices = *v;
    float *positions;
    float *colors;

    // Get vertex positions.
    positions = new float[vertices.size() * 4];
    for (uint32_t i = 0; i < vertices.size(); i++) {
        positions[i + 0] = vertices[i].x;
        positions[i + 1] = vertices[i].y;
        positions[i + 2] = vertices[i].z;
        positions[i + 3] = 1.0f;
    }

    // Point to vertex positions.
    //::glBindBuffer(GL_ARRAY_BUFFER, m_positions);
    //::glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, positions, GL_STATIC_DRAW);
    //::glEnableVertexAttribArray(0);
    //::glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    ::glVertexAttrib4fv(0, positions);

    // Get vertex colors.
    colors = new float[vertices.size() * 3];
    for (uint32_t i = 0; i < vertices.size(); i++) {
        colors[i + 0] = vertices[i].r;
        colors[i + 1] = vertices[i].g;
        colors[i + 2] = vertices[i].b;
        colors[i + 3] = vertices[i].a;
    }

    // Point to vertex colors.
    //::glBindBuffer(GL_ARRAY_BUFFER, m_colors);
    //::glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, colors, GL_STATIC_DRAW);
    //::glEnableVertexAttribArray(1);
    //::glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    ::glVertexAttrib4fv(1, colors);

    // Render.
    ::glDrawArrays(GL_TRIANGLES, 0, vertices.size() * 4);
    
    // Clean up.
    ::glDisableVertexAttribArray(0);
    ::glDisableVertexAttribArray(1);
}
