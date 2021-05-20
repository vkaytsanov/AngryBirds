#pragma once
#include "entityx/Entity.h"

enum PrefabType {
	Undefined,
	Pig,
	RedBirdBig,
};

class PrefabDatabase {
public:
	void generatePrefab(entityx::Entity entity, PrefabType type);
};
