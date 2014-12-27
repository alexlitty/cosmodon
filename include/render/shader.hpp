#ifndef COSMODON_RENDER_SHADER_HPP
#define COSMODON_RENDER_SHADER_HPP

#include <string>

namespace cosmodon
{
    /**
     * A shader.
     *
     * Controls how graphics are rendered.
     */
    class shader
    {
    public:
        // Possible shader levels.
        enum level_type
        {
            vertex,
            fragment,
            geometry,
        };

        // Shader level.
        level_type level;

        // Shader code.
        std::string code;

        /**
         * Constructor.
         */
        shader(level_type init_level, std::string init_code = "");
    };
}

#endif
