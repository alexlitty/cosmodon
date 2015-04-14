#include <common/random.hpp>

// Seeds random operations with the current time.
void cosmodon::random::seed()
{
    cosmodon::random::seed(std::time(0));
}

// Seeds random operations.
void cosmodon::random::seed(uint32_t value)
{
    std::srand(value);
}

// Generates a random integer.
uint32_t cosmodon::random::integer(uint32_t min, uint32_t max)
{
    return std::rand() % (max - min + 1) + min;
}
