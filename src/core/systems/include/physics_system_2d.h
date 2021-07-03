#pragma once

#include "entityx/System.h"

#include "box2d-emscripten/Dynamics/b2World.h"
#include "../../data/include/config_development.h"


#if defined(_DEBUG) && defined(BOX2D_DEBUG_DRAW)
#include "utils/box2d/b2draw/DebugDraw.h"
#endif


class PhysicsSystem2D : public entityx::System<PhysicsSystem2D> {
private:
	b2World m_world;
#if defined(_DEBUG) && defined(BOX2D_DEBUG_DRAW)
	b2draw::DebugDraw m_debugDraw;
#endif
public:
	PhysicsSystem2D();
public:
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void configure(entityx::EventManager& events) override;
	void initializeBodies(entityx::EntityManager& entities);

	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
#if defined(_DEBUG) && defined(BOX2D_DEBUG_DRAW)
	b2draw::DebugDraw* getDebugDraw();
#endif
};
