#include <render/shader.hpp>

// Constructor.
cosmodon::shader::shader(cosmodon::shader::level_type init_level, std::string init_code)
  : level(init_level), code(init_code)
{
    // If necessary, set default shader code.
    if (code == "") {

        // Vertex shader.
        if (level == cosmodon::shader::level_type::vertex) {
            code = "#version 130\n"
                   "\n"
                   "in vec4 position;\n"
                   "\n"
                   "void main()\n"
                   "{\n"
                   "    gl_Position = gl_Vertex;\n"
                   "}";
        }

        // Fragment shader.
        else {
            code = "#version 130\n"
                   "\n"
                   "\n"
                   "void main()\n"
                   "{\n"
                   "    gl_FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
                   "}";
        }
    }
}
