//
// Created by Viktor on 22.05.2021 г..
//

#include "include/playing_screen.h"
#include "../components/2d/include/animator.h"
#include "../components/2d/include/rigid_body_2d.h"
#include "../components/include/pig.h"

#include "../data/include/box2d_database.h"
#include "../data/include/entity_factory.h"
#include "../include/game_state_manager.h"
#include "../systems/include/physics_system_2d.h"
#include "../systems/include/bird_system.h"


PlayingScreen::PlayingScreen(GameStateManager* gameStateManager) : AbstractScreen(gameStateManager) {
}

void PlayingScreen::start(entityx::EntityX* entityX) {
	// clear all entities
	AbstractScreen::start(entityX);
	
	// load the background, ground and back sling
	EntityFactory::createBackground(entityX->entities);
	auto ground = EntityFactory::createGround(entityX->entities);
	ground.addComponent<RigidBody2D>(Box2dDatabase::getInstance().m_groundBody);

	EntityFactory::createBackSling(entityX->entities);
	
	// load the birds, pigs, collision objects
	m_sceneManager.changeScene(&entityX->entities, std::to_string(m_pGameStateManager->m_currentLevel));

	
	
	// FIXME: we should create event for round start
	// and clear the birds queue inside the system
	auto& birdsQueue = entityX->systems.system<BirdSystem>()->m_birds;
	while(!birdsQueue.empty()) {
		birdsQueue.pop();
	}
	// add the birds to the bird system
	entityX->systems.system<BirdSystem>()->addBird(entityX->entities, Red);
	entityX->systems.system<BirdSystem>()->addBird(entityX->entities, Terence);
	entityX->systems.system<BirdSystem>()->addBird(entityX->entities, Chuck);
	
	// create front sling over all the birds
	EntityFactory::createFrontSling(entityX->entities);
	// initialize bodies
	entityX->systems.system<PhysicsSystem2D>()->initializeBodies(entityX->entities);
}

