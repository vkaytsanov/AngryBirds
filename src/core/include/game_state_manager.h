//
// Created by Viktor on 16.2.2021 г..
//

#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H


enum GameState {
	Menu,
	Playing,
};


class GameStateManager {
private:
	GameState m_lastState;
	GameState m_currentState;
public:
	GameStateManager();
	~GameStateManager();
	GameState getCurrentState() const;
	const char* getCurrentStateName() const;
	void changeState(GameState nextState);
	void update();
	bool hasChanged() const;
};

#endif //GAME_STATE_MANAGER_H
