#pragma once
#include "entity_type.h"

#include "entityx/Entity.h"



class EntityFactory {
public:
	static entityx::Entity createEntityFromType(entityx::EntityManager& entities, EntityType type);
};
