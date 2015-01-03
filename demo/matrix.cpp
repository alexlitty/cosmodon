#include <cosmodon.hpp>
#include "test.hpp"

namespace cosmodon
{
    namespace demo
    {
        void matrix()
        {
            cosmodon::matrix I, A, B, C;
            cosmodon::vector result;

            // Output start.
            std::cout << "Starting Vector: " << result << std::endl << std::endl;

            // Perform test.
            A.translate(16, 7, -4);
            B.scale(2, 2, 2);
            C = B * A;

            // Transform matrix.
            result = C * result;

            // Output result.
            std::cout << "Result Matrix:\n" << C << std::endl << std::endl;
            std::cout << "Result Vector: " << result << std::endl;
        }
    }
}
