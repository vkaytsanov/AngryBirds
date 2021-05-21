#pragma once
#include <queue>

#include "entityx/System.h"
#include "utils/geometry/include/vector3.h"
#include "../../data/include/entity_type.h"

class BirdSystem : public entityx::System<BirdSystem>{
private:
	std::queue<entityx::Entity> m_birds;
	entityx::Entity m_currentBird;
	b2Vec2 m_slingShotStartPos = b2Vec2(-64.f, -9.5f);
	b2Vec2 m_maxStretchDistance = b2Vec2(7.5f, 7.5f);
	float forceMultiplier = 25'000;
	bool m_selected = false;
	void handleInput();
	void useChuckAbility();
public:
	static bool m_canSlingshot;
public:
	void addBird(entityx::EntityManager& entities, EntityType type);
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void configure(entityx::EventManager& events) override;
	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
};
