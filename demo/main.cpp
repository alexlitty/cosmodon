#include <cosmodon.hpp>
#include <render/opengl.hpp>
#include "test.hpp"

int main()
{
    uint8_t i;
    cosmodon::clock timer;
    cosmodon::rate fps;

    try {
        cosmodon::number value = 0.01;
        cosmodon::vector up;
        cosmodon::camera camera;

        // Prepare rendered objects.
        cosmodon::shape::pyramid shape(0.5f, 0.3f);

        // Camera orientation.
        camera.set_position(0.0f, 0.0f, 0.5f);
        up = camera.get_position();
        up.y = 1.0f;
        camera.set_orientation(shape.get_position(), up);

        // Camera perspective.
        camera.set_perspective(90, 1024.0f / 768.0f, 0.01f, 1.0f);
        std::cout << "Matrix: " << camera.get_perspective() << std::endl;
        std::cout << "Normal vertex: " << shape[0] << std::endl;

        cosmodon::vector test = shape[0] * camera.get_perspective();

        std::cout << "Perspective result: " << test << std::endl;

        // Start OpenGL window.
        cosmodon::opengl window(1024, 768, "Cosmodon Demo");
        window.set_camera(camera);

        // Set default shaders.
        cosmodon::shader vertex(cosmodon::shader::vertex), fragment(cosmodon::shader::fragment);
        window.set_shaders(&vertex, &fragment);

        // Perform demo.
        //bool rotate = true;
        //cosmodon::number z = 0;
        while (true) {
            // Transform shape.
            if (i++ <= 255) {
                //shape.rotate(0, value, 0);
                //shape.scale(value, value, value);
                i = 0;

                // Rotate shape.
                /*if (rotate) {
                    value += 0.01;
                    if (value >= 0.5f) {
                        rotate = false;
                    }

                } else {
                    value -= 0.01;
                    if (value <= -0.5f) {
                        rotate = true;
                    }
                }*/
                value += 0.05;
                shape.rotate(value, 0, 0);
            }

            // Transform z-clipping.

            // Display shape.
            window.clear(cosmodon::black);
            window.render(&shape);
            window.display();

            // Update FPS.
            fps.tally();
            if (timer.elapsed(cosmodon::unit::millisecond) > 100) {
                timer.reset();
                window.set_window_title(std::to_string(fps.get()));
            }
        }
    }

    // Catch errors.
    catch (cosmodon::exception::base &e) {
        std::cout << e.what() << std::endl;
    }
}
