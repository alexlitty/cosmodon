#include <exception.hpp>
#include <window.hpp>

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
    ::glGenBuffers(1, &m_buffer);
}

// Destructor.
cosmodon::window::~window()
{
    ::glDeleteBuffers(1, &m_buffer);
    ::glfwDestroyWindow(m_handle);
    ::glfwTerminate();
}

// Clear the window using a color.
void cosmodon::window::clear(cosmodon::color &color)
{
    ::glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
    ::glClear(GL_COLOR_BUFFER_BIT);
    ::glfwSwapBuffers(m_handle);
}

// Render vertices to the window.
void cosmodon::window::render(cosmodon::primitive primitive, const float *vertices, uint32_t count)
{
    // Load vertices into GPU buffer.
    ::glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
    ::glBufferData(GL_ARRAY_BUFFER, count, vertices, GL_STATIC_DRAW);

    // ... ?
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // Render.
    glDrawArrays(GL_TRIANGLES, 0, count);

    // Unbind buffer.
    ::glBindBuffer(GL_ARRAY_BUFFER, 0);
}
