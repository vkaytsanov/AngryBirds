//
// Created by Viktor on 22.05.2021 г..
//

#include "include/playing_screen.h"
#include "../components/2d/include/animator.h"
#include "../components/2d/include/rigid_body_2d.h"
#include "../components/2d/include/sprite.h"
#include "../components/include/particle_emitter.h"
#include "../components/include/pig.h"

#include "../data/include/asset_manager.h"
#include "../data/include/box2d_database.h"
#include "../data/include/entity_factory.h"
#include "utils/include/animation.h"
#include "../data/include/animators_database.h"
#include "../systems/include/physics_system_2d.h"


PlayingScreen::PlayingScreen(GameStateManager* gameStateManager) : AbstractScreen(gameStateManager) {
}

void PlayingScreen::start(entityx::EntityX* entityX) {
	AbstractScreen::start(entityX);
	// clear all entities
	// load the background, ground and back sling
	EntityFactory::createBackground(entityX->entities);
	EntityFactory::createGround(entityX->entities);
	EntityFactory::createEntityFromType(entityX->entities, WoodRectangle);
	EntityFactory::createEntityFromType(entityX->entities, WoodSquare);
	EntityFactory::createEntityFromType(entityX->entities, WoodSquare);
	EntityFactory::createEntityFromType(entityX->entities, WoodSquare);
	EntityFactory::createEntityFromType(entityX->entities, WoodSquare);
	EntityFactory::createEntityFromType(entityX->entities, WoodSquare);
	EntityFactory::createEntityFromType(entityX->entities, WoodSquare);
	EntityFactory::createEntityFromType(entityX->entities, WoodSquare);
	EntityFactory::createEntityFromType(entityX->entities, WoodSquare);
	EntityFactory::createEntityFromType(entityX->entities, WoodSquare);
	// load the birds, pigs, collision objects
	// add the birds to the bird system
	
	// initialize bodies
	entityX->systems.system<PhysicsSystem2D>()->initializeBodies(entityX->entities);
}

