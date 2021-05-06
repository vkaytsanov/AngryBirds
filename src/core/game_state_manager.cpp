//
// Created by Viktor on 16.2.2021 г..
//

#include "include/game_state_manager.h"

GameStateManager::GameStateManager() {
	m_currentState = Playing;
}


GameState GameStateManager::getCurrentState() const {
	return m_currentState;
}


void GameStateManager::changeState(const GameState nextState) {
	m_currentState = nextState;
}

const char* GameStateManager::getCurrentStateName() const {
	switch ((m_currentState)) {
		case Playing:
			return "Playing";
		default:
			return nullptr;
	}
}

GameStateManager::~GameStateManager() {

}




