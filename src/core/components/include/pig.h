#pragma once

#include "../../data/include/entity_type.h"

typedef EntityType PigType;

struct Pig {
	PigType type;

	Pig() : type(PigMinion){}
	Pig(const PigType type) : type(type){}
};
