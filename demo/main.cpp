#include <cosmodon.hpp>
#include <render/opengl.hpp>
#include "test.hpp"

int main()
{
    cosmodon::clock timer;
    cosmodon::rate fps;

    try {
        // Perform matrices tests.
        cosmodon::demo::matrix();

        // Start OpenGL window.
        /*cosmodon::opengl window(1024, 768, "Cosmodon Demo");
        cosmodon::shape::triangle triangle;

        // Set default shaders.
        cosmodon::shader vertex(cosmodon::shader::vertex), fragment(cosmodon::shader::fragment);
        window.set_shaders(&vertex, &fragment);

        // Perform demo.
        while (true) {
            window.clear(cosmodon::black);
            window.render(&triangle);
            window.display();

            // Update FPS.
            fps.tally();
            if (timer.elapsed(cosmodon::unit::millisecond) > 100) {
                timer.reset();
                window.set_window_title(std::to_string(fps.get()));
            }
        }*/
    }

    // Catch errors.
    catch (cosmodon::exception::base &e) {
        std::cout << e.what() << std::endl;
    }
}
