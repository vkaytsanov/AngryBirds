#include "include/entity_factory.h"

#include "../components/include/transform.h"
#include "../components/include/pig.h"
#include "../components/include/bird.h"
#include "../components/include/obstacle.h"
#include "../components/2d/include/rigid_body_2d.h"
#include "../components/2d/include/sprite.h"
#include "../components/2d/include/animator.h"
#include "include/animators_database.h"
#include "include/box2d_database.h"
#include "include/sprite_database.h"

entityx::Entity EntityFactory::createEntityFromType(entityx::EntityManager& entities, EntityType type) {
	auto entity = entities.create();
	entity.addComponent<Transform>();
	entity.addComponent<RigidBody2D>(Box2dDatabase::getInstance().fromTypeToBody(type));
	entity.addComponent<Sprite>(SpriteDatabase::getInstance().fromTypeToSprite(type));
	// TODO can be made better
	if (isAnimated(type)) {
		entity.addComponent<Animator>(AnimatorsDatabase::getInstance().fromTypeToAnimator(type));
		if (isPig(type)) {
			entity.addComponent<Pig>(type);
		}
		else {
			entity.addComponent<Bird>(type);
		}
	}
	else {
		entity.addComponent<Obstacle>(type);
	}
	return entity;
}

entityx::Entity EntityFactory::createBackground(entityx::EntityManager& entities) {
	auto background = entities.create();
	auto ts = background.addComponent<Transform>();
	ts->scale = Vector3f(5, 5, 1);
	background.addComponent<Sprite>(SpriteDatabase::getInstance().getBackground());
	return background;
}

entityx::Entity EntityFactory::createGround(entityx::EntityManager& entities) {
	auto ground = entities.create();
	auto ts = ground.addComponent<Transform>(Vector3f(0, -50, 0));
	ts->scale = Vector3f(10, 1.4f, 1);
	
	ground.addComponent<Sprite>(SpriteDatabase::getInstance().getGround());
	return ground;
}

entityx::Entity EntityFactory::createBackSling(entityx::EntityManager& entities) {
	auto backSling = entities.create();
	auto ts = backSling.addComponent<Transform>();
	ts->position = Vector3f(-60, -16, 0);
	backSling.addComponent<Sprite>(SpriteDatabase::getInstance().getBackSlingshot());
	
	return backSling;
}


entityx::Entity EntityFactory::createFrontSling(entityx::EntityManager& entities) {
	auto frontSling = entities.create();
	auto ts2 = frontSling.addComponent<Transform>();
	ts2->position = Vector3f(-63.7f, -10.4f, 0);
	frontSling.addComponent<Sprite>(SpriteDatabase::getInstance().getFrontSlingshot());
	
	return frontSling;
}
