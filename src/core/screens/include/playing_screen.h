//
// Created by Viktor on 22.05.2021 г..
//

#ifndef PLAYING_SCREEN_H
#define PLAYING_SCREEN_H


#include "abstract_screen.h"
#include "../../scene_editor/include/scene_manager.h"

class PlayingScreen : public AbstractScreen {
private:
	SceneManager m_sceneManager;
public:
	PlayingScreen(GameStateManager* gameStateManager);
	void start(entityx::EntityX* entityX) override;
};


#endif //PLAYING_SCREEN_H
