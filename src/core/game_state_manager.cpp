//
// Created by Viktor on 16.2.2021 г..
//

#include "include/game_state_manager.h"

GameStateManager::GameStateManager() {
	m_currentState = m_lastState = Menu;
}


GameState GameStateManager::getCurrentState() const {
	return m_currentState;
}


void GameStateManager::changeState(const GameState nextState) {
	m_lastState = m_currentState;
	m_currentState = nextState;
}

void GameStateManager::update() {
	m_lastState = m_currentState;
}

bool GameStateManager::hasChanged() const {
	return m_lastState != m_currentState;
}

const char* GameStateManager::getCurrentStateName() const {
	switch ((m_currentState)) {
		case Playing:
			return "Playing";
		case Menu:
			return "Menu";
	}
}

GameStateManager::~GameStateManager() {

}




