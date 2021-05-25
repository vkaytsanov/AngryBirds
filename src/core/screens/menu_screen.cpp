//
// Created by Viktor on 22.05.2021 г..
//

#include "include/menu_screen.h"
#include "../components/2d/include/sprite.h"
#include "../components/2d/include/button.h"
#include "../include/game_state_manager.h"
#include "../data/include/entity_factory.h"
#include "../data/include/audio_database.h"

void MenuScreen::createPlayButton(entityx::EntityManager& entities) {
	auto m_playButton = entities.create();
		auto transform = m_playButton.addComponent<Transform>();
		transform->scale = Vector3f(2, 2, 1);
		m_playButton.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("ui"), 0, 0, 168, 108));
		auto listener = m_playButton.addComponent<Button>();
		listener->clickListener = [&]() {
			m_pGameStateManager->changeState(Playing);
			AudioDatabase::getInstance().stop(MUSIC_MENU);
			AudioDatabase::getInstance().play(MUSIC_LEVEL_START);
		};
}

MenuScreen::MenuScreen(GameStateManager* gameStateManager) : AbstractScreen(gameStateManager) {
}

void MenuScreen::start(entityx::EntityX* entityX) {
	AbstractScreen::start(entityX);
	AudioDatabase::getInstance().play(MUSIC_MENU, true);
	EntityFactory::createBackground(entityX->entities);
	EntityFactory::createGround(entityX->entities);
	createPlayButton(entityX->entities);
}
