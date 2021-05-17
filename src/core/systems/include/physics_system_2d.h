#pragma once
#include "entityx/System.h"
#include "box2d/b2_world.h"
#include "utils/box2d/b2draw/DebugDraw.h"


class PhysicsSystem2D : public entityx::System<PhysicsSystem2D> {
private:
	b2World m_world;
	b2draw::DebugDraw m_debugDraw;
public:
	PhysicsSystem2D();
	~PhysicsSystem2D() override;
	
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void configure(entityx::EventManager& events) override;
	void initializeBodies(entityx::EntityManager& entities);

	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void postUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	b2draw::DebugDraw* getDebugDraw();
};
