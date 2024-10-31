#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H
#include <random>
#include <ctime>

class RandomNumberGenerator
{
    public:
    RandomNumberGenerator(const RandomNumberGenerator&) = delete;
    RandomNumberGenerator& operator=(const RandomNumberGenerator&) = delete;

    static RandomNumberGenerator& GetInstance();

    int GetIntInRangeInclusive(int min, int max);

    private:
    RandomNumberGenerator();

};

#endif