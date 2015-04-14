#include <render/shape.hpp>

// Generates a rectangle.
void cosmodon::shape::rectangle(cosmodon::vertices &v, number width, number height)
{
    cosmodon::number w = width / 2;
    cosmodon::number h = height / 2;

    cosmodon::vertex top_left(-w, -h, 0.1f);
    cosmodon::vertex top_right(w, -h, 0.1f);
    cosmodon::vertex bottom_left(-w, h, 0.1f);
    cosmodon::vertex bottom_right(w, h, 0.1f);

    v.add(top_right);
    v.add(top_left);
    v.add(bottom_right);
    
    v.add(top_left);
    v.add(bottom_left);
    v.add(bottom_right);

    for (uint32_t i = 0; i < v.size(); i++) {
        v[i].r = 150;
        v[i].g = 25;
        v[i].b = 0;
    }
}
