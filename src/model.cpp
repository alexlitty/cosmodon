#include <model.hpp>

// Constructor.
cosmodon::model::model()
{

}

// Render to window.
void cosmodon::model::render(cosmodon::window &window)
{
    window.render(this);
}
