#pragma once

#include "../../data/include/entity_type.h"
#include "utils/include/sound.h"

typedef EntityType BirdType;

struct Bird {
	BirdType type;
	Sound* collisionSound;
	
	Bird() = default;
	Bird(BirdType type) : type(type){}
};
