#pragma once
#include "entityx/System.h"
#include "../../events/round_over.h"

struct PigKilledEvent;
class GameStateManager;

class GameStateSystem : public entityx::System<GameStateSystem>,
                        public entityx::Receiver<GameStateSystem> {
private:
	GameStateManager* m_pGameStateManager;
	entityx::EntityManager* m_pEntities;
public:
	explicit GameStateSystem(GameStateManager* gameStateManager);
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void receive(const RoundOverEvent& event);
	void receive(const PigKilledEvent& event);
};
