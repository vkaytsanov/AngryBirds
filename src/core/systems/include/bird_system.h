#pragma once
#include <queue>

#include "entityx/System.h"
#include "utils/geometry/include/vector3.h"

class BirdSystem : public entityx::System<BirdSystem>{
private:
	std::queue<entityx::Entity> m_birds;
	Vector3f m_slingShotStartPos = Vector3f(-64.f, -9.5f, 0);
	float forceMultiplier = 30'000;
	bool m_selected = false;
	void handleInput();
public:
	static bool m_canSlingshot;
public:
	void initializeCurrentRound(std::vector<entityx::Entity>& birds);
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void configure(entityx::EventManager& events) override;
	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
};
