//
// Created by Viktor on 16.2.2021 г..
//

#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H


enum GameState {
	Menu,
	Playing,
	GameLost,
	GameWon
};


class GameStateManager {
	friend class GameStateSystem;
private:
	GameState m_lastState;
	GameState m_currentState;
public:
	int m_currentLevel = 1;
public:
	GameStateManager();
	~GameStateManager() = default;
public:
	GameState getCurrentState() const;
	const char* getCurrentStateName() const;
	void changeState(GameState nextState);
	void update();
	bool hasChanged() const;
};

#endif //GAME_STATE_MANAGER_H
