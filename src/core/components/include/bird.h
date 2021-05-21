#pragma once

#include "../../data/include/entity_type.h"

typedef EntityType BirdType;

struct Bird {
	BirdType type;

	Bird() = default;
	Bird(BirdType type) : type(type){}
};
