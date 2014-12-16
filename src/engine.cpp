#include <engine.hpp>

// Engine constructor.
cosmodon::engine::engine(cosmodon::layer *root)
{
    set_layer(root);
}

// Engine destructor.
cosmodon::engine::~engine()
{
    delete m_layer;
}

// Perform engine program.
bool cosmodon::engine::execute()
{
    while (m_layer != nullptr) {
        if (!m_layer->execute()) {
            delete m_layer;
            m_layer = nullptr;
        }
    }
    return false;
}

// Set the layer root, returning the old root.
cosmodon::layer* cosmodon::engine::set_layer(cosmodon::layer *root)
{
    cosmodon::layer *old_layer = m_layer;
    m_layer = root;
    return old_layer;
}
