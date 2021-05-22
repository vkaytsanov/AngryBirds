//
// Created by Viktor on 22.05.2021 г..
//

#include "include/menu_screen.h"
#include "../components/2d/include/sprite.h"
#include "../components/2d/include/button.h"
#include "../include/game_state_manager.h"

MenuScreen::MenuScreen(GameStateManager* gameStateManager) : AbstractScreen(gameStateManager){
	std::shared_ptr<Texture> texture = AssetManager::getInstance().getSprite("ui");
	auto m_playButton = m_entities.create();
	auto transform = m_playButton.addComponent<Transform>();
	transform->scale = Vector3f(2, 2, 1);
	m_playButton.addComponent<Sprite>(TextureRegion(texture, 0, 0, 168, 108));
	auto listener = m_playButton.addComponent<Button>();
	listener->clickListener = [&]() {
		Lib::app->log("ClickListener", "im listening");
		m_pGameStateManager->changeState(Playing);
	};
}


