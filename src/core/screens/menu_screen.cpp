//
// Created by Viktor on 22.05.2021 г..
//

#include "include/menu_screen.h"
#include "../components/2d/include/sprite.h"
#include "../components/2d/include/button.h"
#include "../include/game_state_manager.h"

MenuScreen::MenuScreen(GameStateManager* gameStateManager) : AbstractScreen(gameStateManager) {
	std::shared_ptr<Texture> texture = AssetManager::getInstance().getSprite("ui");
	{
		auto background = m_entities.create();
		auto ts = background.addComponent<Transform>();
		ts->scale = Vector3f(25, 20, 1);
		background.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("background")));
	}
	
	{
		auto m_playButton = m_entities.create();
		auto transform = m_playButton.addComponent<Transform>();
		transform->scale = Vector3f(2, 2, 1);
		m_playButton.addComponent<Sprite>(TextureRegion(texture, 0, 0, 168, 108));
		auto listener = m_playButton.addComponent<Button>();
		listener->clickListener = [&]() {
			m_pGameStateManager->changeState(Playing);
		};
	}

	{
		auto ground = m_entities.create();
		auto ts = ground.addComponent<Transform>(Vector3f(0, -50, 0));
		ts->scale = Vector3f(10, 1.4f, 1);
		TextureRegion groundTR = TextureRegion(AssetManager::getInstance().getSprite("ground"));
		groundTR.setTiling(10, 1);
		ground.addComponent<Sprite>(std::move(groundTR));
	}
}
