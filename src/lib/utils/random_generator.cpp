//
// Created by Viktor on 1.3.2021 г..
//

#include "include/random_generator.h"

RandomGenerator::RandomGenerator() : generator(std::random_device()()){

}

int RandomGenerator::getRandom(int upperBound) {
	return distribution(generator) % upperBound;
}
