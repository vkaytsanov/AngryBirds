#pragma once

#include <array>

#include "abstract_screen.h"
#include "game_won_window.h"
#include "playing_screen.h"
#include "game_lost_window.h"
#include "menu_screen.h"
#include "../../include/game_state_manager.h"

class ScreenManager {
private:
	GameStateManager m_gameStateManager;
	MenuScreen m_menuScreen;
	PlayingScreen m_playingScreen;
	GameWonWindow m_gameWonWindow;
	GameLostWindow m_gameLostWindow;
	std::array<AbstractScreen*, 4> m_screens;
public:
	entityx::EntityX m_entityX;
	ScreenManager();
	void update();
};
