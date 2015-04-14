#include <render/shape.hpp>

// Pyramid shape.
void cosmodon::shape::pyramid(cosmodon::vertices &v, cosmodon::number width, cosmodon::number height)
{
    cosmodon::number w = width / 2;
    cosmodon::vertex top(0, 0, height);
    cosmodon::vertex northeast(w, w, 0.1f);
    cosmodon::vertex northwest(-w, w, 0.1f);
    cosmodon::vertex southeast(w, -w, 0.1f);
    cosmodon::vertex southwest(-w, -w, 0.1f);

    // Base.
    v.add(northeast);
    v.add(northwest);
    v.add(southeast);

    v.add(southwest);
    v.add(southeast);
    v.add(northwest);

    // First side.
    v.add(top);
    v.add(northwest);
    v.add(northeast);

    // Second side.
    v.add(top);
    v.add(northwest);
    v.add(southwest);

    // Third side.
    v.add(top);
    v.add(southwest);
    v.add(southeast);

    // Fourth side.
    v.add(top);
    v.add(southeast);
    v.add(northeast);

    // Assign vertex colors.
    for (uint8_t i = 0; i < v.size(); i++) {
        v[i].r = 255 - (i * 10);
        v[i].g = 255 - (i * 10);
        v[i].b = 150;
    }
}
