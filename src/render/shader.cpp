#include <render/shader.hpp>

// Constructor.
cosmodon::shader::shader(cosmodon::shader::level_type init_level, std::string init_code)
  : level(init_level), code(init_code)
{
    // If necessary, set default shader code.
    if (code == "") {

        // Vertex shader.
        if (level == cosmodon::shader::level_type::vertex) {
            code = "#version 330\n"
                   "\n"
                   "layout (location = 0) in vec4 position;\n"
                   "layout (location = 1) in vec4 color;\n"
                   "smooth out vec4 frag_color;\n"
                   "\n"
                   "void main()\n"
                   "{\n"
                   "    gl_Position = position;\n"
                   "    frag_color = color;\n"
                   "}";
        }

        // Fragment shader.
        else {
            code = "#version 330\n"
                   "\n"
                   "smooth in vec4 frag_color;\n"
                   "out vec4 out_color;\n"
                   "\n"
                   "void main()\n"
                   "{\n"
                   "    out_color = vec4(1.0, 0.0f, 1.0f, 1.0f);\n"
                   "}";
        }
    }
}
