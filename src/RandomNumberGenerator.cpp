#include "./headers/RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator()
{
    //Seeds are random, as this is a singleton this will only happen once.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

RandomNumberGenerator& RandomNumberGenerator::GetInstance()
{
    static RandomNumberGenerator instance;
    return instance;
}

int RandomNumberGenerator::GetIntInRangeInclusive(int min, int max)
{
    return min + (std::rand() % (max - min + 1));
}