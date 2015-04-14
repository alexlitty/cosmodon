#include <cosmodon.hpp>
#include <draw/opengl.hpp>
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
        cosmodon::model object;
        cosmodon::shape::pyramid(object, 0.1f, 0.3f);
        cosmodon::shape::rectangle(object, 0.1f, 0.2f);
        object.set_position(0.00f, 0, 0.15f);

        // Color rendered objects.
        cosmodon::color test;
        for (uint32_t i = 0; i < object.size(); i++) {
            test.r = cosmodon::random::integer(0, 255);
            test.g = cosmodon::random::integer(0, 255);
            test.b = cosmodon::random::integer(0, 255);
            object[i] = test;
        }

        // Camera view options.
        camera.set_position(0.0f, 0.0f, -0.1f);
        up = camera.get_position();
        up.y = 1.0f;
        camera.set_orientation(up);
        camera.set_target(object.get_position());

        // Camera projection options.
        camera.set_fov(90);
        camera.set_aspect(1024.0f / 768.0f);
        camera.set_clipping(0.001f, 100.0f);

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
                b = 0.001;

                object.rotate(a, 0, 0);
                object.move(b, 0, 0);
                camera.set_target(object);
            }

            // Transform z-clipping.

            // Prepare window.
            window.clear(cosmodon::black);

            // Render shape outline.
            //shape.set_scale(1);
            object.set_fill(false);
            window.draw(&object);

            // Render shape.
            //shape.set_scale(0.8);
            object.set_fill(true);
            window.draw(&object);

            // Display window.
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
