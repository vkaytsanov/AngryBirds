﻿#include "include/physics_system_2d.h"
#include "../components/2d/include/rigid_body_2d.h"
#include "../components/include/transform.h"


PhysicsSystem2D::PhysicsSystem2D() : m_world(b2Vec2(0, -9.8f)),
                                    m_debugDraw(0, 1) {
	m_debugDraw.SetFlags(0xff);
	m_world.SetDebugDraw(&m_debugDraw);
}


void PhysicsSystem2D::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
}

void PhysicsSystem2D::configure(entityx::EventManager& events) {
}

void PhysicsSystem2D::initializeBodies(entityx::EntityManager& entities) {
	for (auto entity : entities.entities_with_components<RigidBody2D>()) {
		Vector3f& position = entity.getComponent<Transform>()->position;
		entityx::ComponentHandle<RigidBody2D> ch = entity.getComponent<RigidBody2D>();
		ch->bodyDef.position = b2Vec2(position.x, position.y);
		ch->body = m_world.CreateBody(&ch->bodyDef);

		ch->body->CreateFixture(&ch->fixtureDef);
	}
}

PhysicsSystem2D::~PhysicsSystem2D() {
}

void PhysicsSystem2D::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events,
                                entityx::TimeDelta dt) {
	static const int32_t velocityIterations = 5;
	static const int32_t positionIterations = 3;
	// static const float fixedDeltaTime = 0.0016f;
	m_world.Step(dt, velocityIterations, positionIterations);

	for (auto entity : entities.entities_with_components<RigidBody2D>()) {
		entityx::ComponentHandle<RigidBody2D> rb = entity.getComponent<RigidBody2D>();

		if (rb->body->IsAwake()) {
			entityx::ComponentHandle<Transform> t = entity.getComponent<Transform>();
			b2Vec2 p = rb->body->GetPosition();

			t->position = Vector3f(p.x, p.y, 0);
			t->eulerAngles = Vector3f(0, 0, rb->body->GetAngle() * MathUtils::RAD2DEG);
			t->hasChanged = true;

			// Lib::app->log("Rotation: ", (rb->body->GetAngle()));
		}
	}

	m_debugDraw.Clear();
	m_world.DebugDraw();
	m_debugDraw.BufferData();
}

void PhysicsSystem2D::postUpdate(entityx::EntityManager& entities, entityx::EventManager& events,
                                 entityx::TimeDelta dt) {

}

b2draw::DebugDraw* PhysicsSystem2D::getDebugDraw() {
	return &m_debugDraw;
}