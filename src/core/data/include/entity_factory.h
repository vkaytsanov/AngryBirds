#pragma once
#include "entity_type.h"

#include "entityx/Entity.h"



class EntityFactory {
public:
	static entityx::Entity createEntityFromType(entityx::EntityManager& entities, EntityType type);
	static entityx::Entity createBackground(entityx::EntityManager& entities);
	static entityx::Entity createGround(entityx::EntityManager& entities);
	static entityx::Entity createBackSling(entityx::EntityManager& entities);
	static entityx::Entity createFrontSling(entityx::EntityManager& entities);
};
