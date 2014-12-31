#include <cosmodon.hpp>
#include "test.hpp"

namespace cosmodon
{
    namespace demo
    {
        void matrix()
        {
            cosmodon::matrix I, A, B, C;

            // Set all to identity.
            I.identity();
            A.identity();
            B.identity();
            C.identity();

            // Perform test.
            A.translate(16, 7, -4);
            //B.rotate_x(cosmodon::math::pi / 3);
            C = A * B * I;

            // Output result.
            std::cout << "Result Matrix:\n" << C << std::endl << std::endl;
        }
    }
}
