//
// Created by Viktor on 1.3.2021 г..
//

#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>

class RandomGenerator {
private:
	std::mt19937 generator;
	std::uniform_int_distribution<int> distribution;
public:
	RandomGenerator();
	int getRandom(int upperBound);
};


#endif //RANDOM_GENERATOR_H
