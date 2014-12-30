#include <cosmodon.hpp>
#include "test.hpp"

namespace cosmodon
{
    namespace demo
    {
        void matrix()
        {
            cosmodon::matrix<4, 4> A, B, C;
            A = 5;
            B = 2;
            C = A * B;

            // Test zero'ing
            std::cout << "A:\n" << A << std::endl << std::endl;
            std::cout << "B:\n" << B << std::endl << std::endl;
            std::cout << "C:\n" << C << std::endl;
        }
    }
}
