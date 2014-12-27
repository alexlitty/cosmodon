#include <exception.hpp>
#include <window.hpp>

// @@@
#include <unistd.h>

// Constructor.
cosmodon::window::window(cosmodon::render::driver *driver, GLFWwindow *handle)
{
    m_driver = driver;
    m_handle = handle;
}

// Destructor.
cosmodon::window::~window()
{

}

// Clear the window using a color.
void cosmodon::window::clear(cosmodon::color color)
{
    m_driver->clear(color);
}

// Render vertices to the window.
void cosmodon::window::render(cosmodon::vertices *v)
{
    m_driver->render(v);
}

// Display currently rendered graphics on the window.
void cosmodon::window::display()
{
    // Calculate FPS.
    m_fps.tally();

    // Display graphics. @@@ Change when implementing multiple windows.
    ::glfwSwapBuffers(m_handle);
}

// Retrieve current FPS.
uint16_t cosmodon::window::fps() const
{
    return m_fps.get();
}
