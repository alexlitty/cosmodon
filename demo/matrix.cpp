#include <cosmodon.hpp>
#include "test.hpp"

namespace cosmodon
{
    namespace demo
    {
        void matrix()
        {
            cosmodon::matrix<4, 4> A, B;
            A.identity();
            B.zero();
        }
    }
}
