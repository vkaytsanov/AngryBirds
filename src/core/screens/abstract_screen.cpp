//
// Created by Viktor on 17.12.2020 г..
//

#include "include/abstract_screen.h"


AbstractScreen::AbstractScreen(GameStateManager* gameStateManager) : m_entities(m_eventManager),
                                                                     m_pGameStateManager(gameStateManager) {
}

void AbstractScreen::start(entityx::EntityX* entityX) {
	for (auto entity : entityX->entities.entities_with_components<Transform>()) {
		entity.destroy();
	}
	entityX->entities.softReset();

	for (auto entity : m_entities.entities_with_components<Transform>()) {
		entityX->entities.create_from_copy(entity);
	}
}
