#ifndef COSMODON_PHYSICS_BOUNDARIES_BOX_HPP
#define COSMODON_PHYSICS_BOUNDARIES_BOX_HPP

namespace cosmodon
{
    namespace boundaries
    {
        class box : public model
        {
        public:
            void resize(number width, number height);
        };
    }
}

#endif
