#pragma once
#include "entityx/Entity.h"
#include "../../data/include/entity_type.h"

typedef EntityType ObstacleType;

struct Obstacle : public entityx::Component<Obstacle> {
	ObstacleType type;

	Obstacle() : type(Undefined) {}
	Obstacle(const ObstacleType type) : type(type) {}
};
