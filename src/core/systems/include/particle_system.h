//
// Created by Viktor on 18.3.2021 г..
//

#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H


#include <queue>

#include "../../../lib/entityx/System.h"
#include "utils/geometry/include/vector3.h"
#include "../../data/include/particle_manager.h"
#include "../../events/the_bird_is_gone.h"

class ParticleSystem : public entityx::System<ParticleSystem>,
                       public entityx::Receiver<ParticleSystem> {
private:
	std::queue<std::pair<Vector3f, ParticleType>> m_queuedEvents;
public:
	ParticleSystem();
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void configure(entityx::EventManager& events) override;
	void receive(const TheBirdIsGone& event);
	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
};


#endif //PARTICLE_SYSTEM_H
