#include "include/game_won_window.h"

#include "../components/2d/include/sprite.h"
#include "../components/2d/include/button.h"
#include "../include/game_state_manager.h"
#include "../data/include/audio_database.h"


GameWonWindow::GameWonWindow(GameStateManager* gameStateManager) : AbstractScreen(gameStateManager){
}

void GameWonWindow::createWindow(entityx::EntityManager& entities) {
	auto texture = AssetManager::getInstance().getSprite("ui");
	auto nextLevelButton = entities.create();
	nextLevelButton.addComponent<Transform>();
	nextLevelButton.addComponent<Sprite>(Sprite(TextureRegion(texture, 0, 178, 60, 50)));
	auto button = nextLevelButton.addComponent<Button>();
	button->clickListener = [&]() {
		m_pGameStateManager->changeState(Playing);
		m_pGameStateManager->m_currentLevel++;
		AudioDatabase::getInstance().stop(MUSIC_LEVEL_CLEAR);
		AudioDatabase::getInstance().play(MUSIC_LEVEL_START);
	};
}

void GameWonWindow::start(entityx::EntityX* entityX) {
	createWindow(entityX->entities);
}
