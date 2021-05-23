//
// Created by Viktor on 22.05.2021 г..
//

#include "include/menu_screen.h"
#include "../components/2d/include/sprite.h"
#include "../components/2d/include/button.h"
#include "../include/game_state_manager.h"
#include "../data/include/entity_factory.h"

MenuScreen::MenuScreen(GameStateManager* gameStateManager) : AbstractScreen(gameStateManager) {
}

void MenuScreen::start(entityx::EntityX* entityX) {
	EntityFactory::createBackground(entityX->entities);
	EntityFactory::createGround(entityX->entities);
	
	auto m_playButton = m_entities.create();
	auto transform = m_playButton.addComponent<Transform>();
	transform->scale = Vector3f(2, 2, 1);
	m_playButton.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("ui"), 0, 0, 168, 108));
	auto listener = m_playButton.addComponent<Button>();
	listener->clickListener = [&]() {
		m_pGameStateManager->changeState(Playing);
	};
}
