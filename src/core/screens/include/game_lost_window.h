#pragma once
#include "abstract_screen.h"

class GameLostWindow : public AbstractScreen {
private:
	void createRestartButton(entityx::EntityManager& entities);
public:
	GameLostWindow(GameStateManager* gameStateManager);
public:
	void start(entityx::EntityX* entityX) override;
};
