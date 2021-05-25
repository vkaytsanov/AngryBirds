//
// Created by Viktor on 17.12.2020 г..
//

#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include "abstract_screen.h"

class MenuScreen : public AbstractScreen {
private:
	void createPlayButton(entityx::EntityManager& entities);
public:
	MenuScreen(GameStateManager* gameStateManager);
	void start(entityx::EntityX* entityX) override;
};


#endif //MENU_SCREEN_H
