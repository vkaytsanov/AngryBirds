#include "include/game_lost_window.h"

#include "../components/include/transform.h"
#include "../components/2d/include/sprite.h"
#include "../components/2d/include/button.h"
#include "../include/game_state_manager.h"
#include "../data/include/audio_database.h"

void GameLostWindow::createRestartButton(entityx::EntityManager& entities) {
	auto texture = AssetManager::getInstance().getSprite("ui");
	auto restartButton = entities.create();
	restartButton.addComponent<Transform>();
	restartButton.addComponent<Sprite>(Sprite(TextureRegion(texture, 0, 484, 60, 50)));
	auto button = restartButton.addComponent<Button>();
	button->clickListener = [&]() {
		// just change to playing state, where it will automatically reset
		// all the entities from #PlayingScreen.start(entityx::EntityX* entityX)
		m_pGameStateManager->changeState(Playing);
		AudioDatabase::getInstance().stop(MUSIC_LEVEL_FAILED);
		AudioDatabase::getInstance().play(MUSIC_LEVEL_START);
	};
}

GameLostWindow::GameLostWindow(GameStateManager* gameStateManager) : AbstractScreen(gameStateManager) {
}

void GameLostWindow::start(entityx::EntityX* entityX) {
	// display the button to restart
	createRestartButton(entityX->entities);
}


