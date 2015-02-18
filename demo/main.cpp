#include <cosmodon.hpp>
#include <render/opengl.hpp>
#include "test.hpp"

int main()
{
    uint8_t i;
    cosmodon::clock timer;
    cosmodon::rate fps;
    cosmodon::number a = 0, b = 0;

    try {
        cosmodon::vector up;
        cosmodon::camera camera;

        // Prepare rendered objects.
        cosmodon::shape::pyramid shape(0.1f, 0.3f);
        shape.set_position(0, 0, 0.25f);

        // Camera orientation.
        camera.set_position(0.1f, 0.1f, 0.0f);
        up = camera.get_position();
        up.x = 1.0f;
        camera.set_orientation(shape.get_position(), up);

        // Camera perspective.
        camera.set_perspective(90, 1024.0f / 768.0f, 0.001f, 999.0f);

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
                a += 0.05;
                b += 0.001;

                shape.rotate(0, 0, a);
                shape.move(0, 0, a * a);
                std::cout << "Shape: " << shape.get_position() << "\n" << shape.get_matrix() << "\n\n";
                //std::cout << "Camera: " << camera.get_position() << "\n" << camera.get_matrix() << "\n\n";
                std::cout << "Total: " << camera.get_perspective() * camera.get_orientation() * shape.get_matrix() * shape.get_position() << std::endl;
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
