#pragma once

#include <array>

#include "abstract_screen.h"
#include "playing_screen.h"
#include "menu_screen.h"
#include "../../include/game_state_manager.h"

class ScreenManager {
private:
	GameStateManager m_gameStateManager;
	MenuScreen m_menuScreen;
	PlayingScreen m_playingScreen;
	std::array<AbstractScreen*, 2> m_screens;
public:
	entityx::EntityX m_entityX;
	ScreenManager();
	void update();
};
