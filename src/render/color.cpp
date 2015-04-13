#include <render/color.hpp>

// Constructor.
cosmodon::color::color(uint8_t init_r, uint8_t init_g, uint8_t init_b, uint8_t init_a) : r(init_r), g(init_g), b(init_b), a(init_a)
{

}

// Copy constructor.
cosmodon::color::color(const cosmodon::color &copy)
  : r(copy.r), g(copy.g), b(copy.b), a(copy.a)
{

}

// Black color.
cosmodon::color cosmodon::black(0, 0, 0);

// White color.
cosmodon::color cosmodon::white(0, 0, 0);

// Red color.
cosmodon::color cosmodon::red(255, 0, 0);

// Green color.
cosmodon::color cosmodon::green(0, 255, 0);

// Blue color.
cosmodon::color cosmodon::blue(0, 0, 255);
