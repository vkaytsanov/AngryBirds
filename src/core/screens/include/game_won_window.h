#pragma once
#include "abstract_screen.h"

class GameWonWindow : public AbstractScreen {
private:
	void createWindow(entityx::EntityManager& entities);
public:
	GameWonWindow(GameStateManager* gameStateManager);
public:
	void start(entityx::EntityX* entityX) override;
};
