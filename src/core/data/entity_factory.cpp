#include "include/entity_factory.h"

#include "../components/include/transform.h"
#include "../components/include/pig.h"
#include "../components/include/bird.h"
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
	if(isAnimated(type)) {
		entity.addComponent<Animator>(AnimatorsDatabase::getInstance().fromTypeToAnimator(type));
		if(isPig(type)) {
			entity.addComponent<Pig>(type);
		}
		else {
			entity.addComponent<Bird>(type);
		}
	}
	return entity;
}
