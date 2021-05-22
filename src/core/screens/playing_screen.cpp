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
	{
		auto background = m_entities.create();
		auto ts = background.addComponent<Transform>();
		ts->scale = Vector3f(25, 20, 1);
		background.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("background")));
	}
	// {
	// entityx::Entity ent = m_entities.create();
	// 	ent.addComponent<Transform>();
	// 	ent.addComponent<RigidBody>();
	// }
	// {
	// entityx::Entity ent = m_entities.create();
	// ent.addComponent<Transform>(Vector3f(5, 3, 2));
	// }

	// 	auto boxObstacleWood = m_entities.create();
	// 	boxObstacleWood.addComponent<Transform>();
	// 	boxObstacleWood.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("blocks"), 709, 0, 82,
	// 	                                                   82));
	// 	boxObstacleWood.addComponent<RigidBody2D>(boxBody, boxDef);

	// 	auto triangleObstacleWood = m_entities.create();
	// 	triangleObstacleWood.addComponent<Transform>();
	// 	triangleObstacleWood.addComponent<Sprite>(
	// 		TextureRegion(AssetManager::getInstance().getSprite("blocks"), 874, 0, 82, 82));
	// 	triangleObstacleWood.addComponent<RigidBody2D>(triangleBody, triangleDef);


	// auto plankObstacleWood = m_entities.create();
	// plankObstacleWood.addComponent<Transform>()->scale = Vector3f(2, 0.4f, 0);
	// plankObstacleWood.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("blocks"), 314, 614, 200,
	//                                                      20));
	// plankObstacleWood.addComponent<RigidBody2D>(Box2dDatabase::getInstance().m_plankBody);

	EntityFactory::createEntityFromType(m_entities, PigMinion);
	// auto normalPig2 = m_entities.create();
	// normalPig2.addComponent<Transform>(Vector3f(0.5, 10, 0));
	// normalPig2.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("pigs"), 679, 790, 99, 97));
	// normalPig2.addComponent<RigidBody2D>(m_bodyDef, m_fixtureDef);
	
	{
		auto ground = m_entities.create();
		auto ts = ground.addComponent<Transform>(Vector3f(0, -50, 0));
		ts->scale = Vector3f(10, 1.4f, 1);
		TextureRegion groundTR = TextureRegion(AssetManager::getInstance().getSprite("ground"));
		groundTR.setTiling(10, 1);
		ground.addComponent<Sprite>(std::move(groundTR));
		ground.addComponent<RigidBody2D>(Box2dDatabase::getInstance().m_groundBody);
	}
	{
		// auto entity = m_entities.create();
		// entity.addComponent<Transform>();
		// entity.addComponent<Sprite>();
		//
		// entity.addComponent<Animator>();
	}
	
	auto backSling = m_entities.create();
	auto ts = backSling.addComponent<Transform>();
	ts->position = Vector3f(-60, -16, 0);
	backSling.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 563, 0, 40, 200));
	
	// m_entityX.systems.system<BirdSystem>()->addBird(m_entityX.entities, Red);
	// m_entityX.systems.system<BirdSystem>()->addBird(m_entityX.entities, Terence);

	auto frontSling = m_entities.create();
	auto ts2 = frontSling.addComponent<Transform>();
	ts2->position = Vector3f(-63.7f, -10.4f, 0);
	
	frontSling.addComponent<Sprite>(TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 733, 160, 43, 125));

}

void PlayingScreen::start(entityx::EntityX* entityX) {
	AbstractScreen::start(entityX);
	// clear all entities
	// load the background, ground and back sling
	// load the birds, pigs, collision objects
	// add the birds to the bird system
	
	// initialize bodies
	entityX->systems.system<PhysicsSystem2D>()->initializeBodies(entityX->entities);
}

