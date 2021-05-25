//
// Created by Viktor on 17.12.2020 г..
//

#include "include/abstract_screen.h"

#include <box2d/b2_world.h>

#include "../components/2d/include/rigid_body_2d.h"


AbstractScreen::AbstractScreen(GameStateManager* gameStateManager) : m_pGameStateManager(gameStateManager) {
}

void AbstractScreen::start(entityx::EntityX* entityX) {
	for(auto entity : entityX->entities.entities_with_components<RigidBody2D>()) {
		auto rb = entity.getComponent<RigidBody2D>()->body;

		rb->GetWorld()->DestroyBody(rb);
	}
	for (auto entity : entityX->entities.entities_with_components<Transform>()) {
		entity.destroy();
	}

	entityX->entities.softReset();
}
