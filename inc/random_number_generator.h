#pragma once

#include <random>
#include <memory>

class RandomNumberGenerator
{
public:
    RandomNumberGenerator(unsigned min, unsigned max);
    unsigned int generateRandomNumber();

private:
    inline static std::default_random_engine randomEngine_;
    std::unique_ptr<std::uniform_int_distribution<unsigned>> distribution_;
};
