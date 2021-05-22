//
// Created by Viktor on 22.05.2021 г..
//

#ifndef ABSTRACT_SCREEN_H
#define ABSTRACT_SCREEN_H

#include "entityx/quick.h"


class GameStateManager;

class AbstractScreen {
protected:
	entityx::EventManager m_eventManager;
	entityx::EntityManager m_entities;

	GameStateManager* m_pGameStateManager;
public:
    AbstractScreen(GameStateManager* gameStateManager);
    virtual ~AbstractScreen() = default;
	virtual void start(entityx::EntityX* entityX);
};


#endif //ABSTRACT_SCREEN_H
