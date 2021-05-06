//
// Created by Viktor on 13.3.2021 г..
//

#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H


#include "../../../lib/entityx/System.h"
#include "../../components/include/transform.h"
#include "../../components/include/rigid_body.h"
#include "../../components/include/box_collider.h"

class PhysicsSystem : public entityx::System<PhysicsSystem>{
private:

	/** TODO: simulating only around the player */
	const int SIMULATING_DISTANCE = 6;
	Transform* m_pPlayerTransform;
	void applyFriction(RigidBody* rigidBody, float dt);

	void applyGravity(RigidBody* rigidBody, float dt);
	void handleCollision(RigidBody* rigidBody, Transform* transform, BoxCollider* boxCollider, Vector3f& acceleration);
public:
	static constexpr float GRAVITY_CONSTANT = 9.81f;
	PhysicsSystem();
	void configure(entityx::EntityManager& entities, entityx::EventManager& events) override;
	void preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
	void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override;
};


#endif //PHYSICS_SYSTEM_H
