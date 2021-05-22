//
// Created by Viktor on 18.3.2021 г..
//

#include "include/particle_system.h"
#include "../components/include/particle_emitter.h"


ParticleSystem::ParticleSystem()  {

}

void ParticleSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
	// m_queuedEvents.push(std::make_pair(Vector3f(0, 0, 0), RedBirdFeathers));

	events.subscribe<TheBirdIsGone>(*this);
}

void ParticleSystem::configure(entityx::EventManager& events) {
}

void ParticleSystem::receive(const TheBirdIsGone& event) {
	ParticleType type;
	switch(event.birdType) {
	case Terence:
	case Red:
		type = RedBirdFeathers;
		break;
	default:
		Lib::app->error("TheBirdIsGoneEvent", "particle type not defined");
	}
	m_queuedEvents.push(std::make_pair(Vector3f(event.position.x, event.position.y, 0), type));
	
}

void ParticleSystem::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	while(!m_queuedEvents.empty()){
		entityx::Entity entity = entities.create();
		entityx::ComponentHandle<ParticleEmitter> emitter = entity.addComponent<ParticleEmitter>(m_queuedEvents.front().second);
		emitter->setToExplosionEmitter();
		emitter->emittingPosition = m_queuedEvents.front().first;
		m_queuedEvents.pop();
	}

	for(entityx::Entity entity : entities.entities_with_components<ParticleEmitter>()){
		entityx::ComponentHandle<ParticleEmitter> emitter = entity.getComponent<ParticleEmitter>();
		emitter->lifetime -= dt;
		 if(!emitter->isAlive()){
		 	entity.destroy();
		 	continue;
		 }
		emitter->update(dt);
	}
}

void ParticleSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {

}

void
ParticleSystem::postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {

}




