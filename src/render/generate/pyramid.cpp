#include <render/generate.hpp>

// Pyramid shape.
void cosmodon::generate::pyramid(cosmodon::vertices &v, cosmodon::number width, cosmodon::number height)
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
}
