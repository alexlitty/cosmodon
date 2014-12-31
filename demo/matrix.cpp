#include <cosmodon.hpp>
#include "test.hpp"

namespace cosmodon
{
    namespace demo
    {
        void matrix()
        {
            cosmodon::matrix<4, 4> I, A, B, C;
            cosmodon::vector<4> vec;
            vec[0] = 5;
            vec[1] = 5;
            vec[2] = 5;
            vec[3] = 1;

            // Set all to identity.
            I.identity();
            A.identity();
            B.identity();
            C.identity();

            // Perform test.
            A.translate(16, 7, -4);
            //B.rotate_x(cosmodon::math::pi / 3);
            C = A * B * I;
            vec = C * vec;

            // Output result.
            std::cout << "Result Matrix:\n" << C << std::endl << std::endl;
            std::cout << "Result Vector: " << vec << std::endl;
        }
    }
}
