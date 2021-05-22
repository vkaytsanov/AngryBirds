#include "include/animator_system.h"
#include "../components/2d/include/animator.h"
#include "../components/include/pig.h"
#include "../data/include/animators_database.h"


void AnimatorSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	// for(auto entity : entities.entities_with_components<Animator>()) {
	// 	entity.getComponent<Sprite>()->getVao()->free();
	// }

	events.subscribe<TheBirdIsGone>(*this);
}

void AnimatorSystem::configure(entityx::EventManager& events) {
}

void AnimatorSystem::receive(const TheBirdIsGone& event) {
	m_shouldSwitchAllPigsToLaughing = true;
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

	if(m_shouldSwitchAllPigsToLaughing) {
		m_shouldSwitchAllPigsToLaughing = false;

		for(auto entity : entities.entities_with_components<Pig>()) {
			entity.getComponent<Animator>()->currentAnimation = PigStates::PigLaughing;
		}
	}
}

void AnimatorSystem::postUpdate(entityx::EntityManager& entities, entityx::EventManager& events,
	entityx::TimeDelta dt) {
}


