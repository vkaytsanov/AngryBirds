#include "include/animator_system.h"
#include "../components/2d/include/animator.h"


void AnimatorSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	for(auto entity : entities.entities_with_components<Animator>()) {
		entity.getComponent<Sprite>()->getVao()->free();
	}
}

void AnimatorSystem::configure(entityx::EventManager& events) {
	// TODO subscribe to Bird collision event and change the animation state of all pigs to laughing
}

void AnimatorSystem::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
}

void AnimatorSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	for(auto entity : entities.entities_with_components<Animator>()) {
		auto sprite = entity.getComponent<Sprite>();
		auto animator = entity.getComponent<Animator>();
		
		sprite->setVao(animator->getFrame().getVao());
		
		animator->animations[animator->currentAnimation].update(dt);
		animator->conditions[animator->currentAnimation](entity, animator->currentAnimation);
	}
}

void AnimatorSystem::postUpdate(entityx::EntityManager& entities, entityx::EventManager& events,
	entityx::TimeDelta dt) {
}


