#pragma once
#include "entityx/System.h"
#include "../../events/the_bird_is_gone.h"

class AnimatorSystem : public entityx::System<AnimatorSystem>,
                       public entityx::Receiver<AnimatorSystem> {
private:
	bool m_shouldSwitchAllPigsToLaughing = false;
public:
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void configure(entityx::EventManager& events) override;
	void receive(const TheBirdIsGone& event);
	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
};
