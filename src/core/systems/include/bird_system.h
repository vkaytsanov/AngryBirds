#pragma once
#include <queue>

#include "entityx/System.h"
#include "utils/geometry/include/vector3.h"
#include "../../data/include/entity_type.h"

struct TheBirdIsGone;

class BirdSystem : public entityx::System<BirdSystem>,
                   public entityx::Receiver<BirdSystem> {
	friend class PlayingScreen;
private:
	std::queue<entityx::Entity> m_birds;
	entityx::Entity m_currentBird;
	b2Vec2 m_slingPos = b2Vec2(-64.f, -8.5f);
	b2Vec2 m_maxDistance = b2Vec2(7.5f, 7.5f);
	float m_forceMultiplier = 35'000;
	bool m_selected = false;
	bool m_canSlingshot = true;
	bool m_isFlying = false;
	bool m_abilityUsed = false;
	bool m_playedSelectedSound = false;
	bool m_eventProcessed = true;
private:
	void handleSlingshotInput();
	void handleBirdAbilityInput();
	void useChuckAbility();
	void useRedAbility();
	void prepareNewBird(entityx::EntityManager& entities, entityx::EventManager& events);
public:
	void addBird(entityx::EntityManager& entities, EntityType type);
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void configure(entityx::EventManager& events) override;
	void receive(const TheBirdIsGone& event);
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
};
