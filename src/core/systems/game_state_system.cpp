#include "include/game_state_system.h"

#include "../include/game_state_manager.h"
#include "../data/include/audio_database.h"

struct Pig;

GameStateSystem::GameStateSystem(GameStateManager* gameStateManager) : m_pGameStateManager(gameStateManager){
}

void GameStateSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	events.subscribe<RoundOverEvent>(*this);
	events.subscribe<PigKilledEvent>(*this);

	m_pEntities = &entities;
}

void GameStateSystem::receive(const RoundOverEvent& event) {
	if(event.isWon) {
		AudioDatabase::getInstance().play(MUSIC_LEVEL_CLEAR);
		m_pGameStateManager->changeState(GameWon);
	}
	else {
		AudioDatabase::getInstance().play(MUSIC_LEVEL_FAILED);
		m_pGameStateManager->changeState(GameLost);
	}
	
}

void GameStateSystem::receive(const PigKilledEvent& event) {
	int pigCount = 0;
	for (auto pig : m_pEntities->entities_with_components<Pig>()) {
		pigCount++;
	}
	// FIXME: it is sent from the #PhysicsSystem2D and we are just setting the
	// animation to disappearing, but not actually destroying the entity
	// immediately
	if (pigCount == 1) {
		// round is won
		AudioDatabase::getInstance().play(MUSIC_LEVEL_CLEAR);
		m_pGameStateManager->changeState(GameWon);
	}
}
