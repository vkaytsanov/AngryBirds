//
// Created by Viktor on 13.3.2021 г..
//

#include "include/physics_system.h"

/** Basic physics system that moves the rigid body based on his current velocity,
 *  applies gravity to it if it has @param m_useGravity set to true,
 *  checks for collisions if the entity has a component BoxCollider, by comparing the neighbour cubes from the current entity's position
 *  if they are Collidable. */

PhysicsSystem::PhysicsSystem(){

}

void PhysicsSystem::configure(entityx::EntityManager& entities, entityx::EventManager& events) {
}

void PhysicsSystem::preUpdate(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {
	for(const auto& entity : entities.entities_with_components<RigidBody>()){
		entityx::ComponentHandle<RigidBody> rigidBody = entity.getComponent<RigidBody>();
		if(rigidBody->m_isActive){
			entityx::ComponentHandle<Transform> transform = entity.getComponent<Transform>();

			//rigidBody->m_velocity = Vector3f(0, 0, 0);
			applyFriction(rigidBody.get(), dt);

			if(rigidBody->m_useGravity){
				applyGravity(rigidBody.get(), dt);
			}
			Vector3f acceleration = rigidBody->m_velocity * dt;
			if(entity.has_component<BoxCollider>()){
				entityx::ComponentHandle<BoxCollider> boxCollider = entity.getComponent<BoxCollider>();
				// so we dont have to update the camera position to be on the top of the bounding box
				boxCollider->updateInverse(transform->position);
				handleCollision(rigidBody.get(), transform.get(), boxCollider.get(), acceleration);
			}
			transform->translate(rigidBody->m_velocity * dt);
		}
	}
}

void PhysicsSystem::update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) {

}

/** Applies friction on the x and z axes to the rigid body's velocity vector, based on his current @param m_drag */
void PhysicsSystem::applyFriction(RigidBody* rigidBody, float dt) {
	float drag = 1.00f - rigidBody->m_drag * dt;
	if(drag < 0.00f) drag = 0.00f;
	rigidBody->m_velocity *= Vector3f(drag, 1, drag);
	if(std::abs(rigidBody->m_velocity.x) < 0.05f) rigidBody->m_velocity.x = 0.0f;
	if(std::abs(rigidBody->m_velocity.y) < 0.05f) rigidBody->m_velocity.y = 0.0f;
	if(std::abs(rigidBody->m_velocity.z) < 0.05f) rigidBody->m_velocity.z = 0.0f;
}

/** Accumulate the effect of gravity on the rigid body's velocity vector */
void PhysicsSystem::applyGravity(RigidBody* rigidBody, float dt) {
	float gravityForce =  rigidBody->m_mass * -GRAVITY_CONSTANT;
	rigidBody->m_velocity.y += gravityForce * dt;
}

/** Checks for collisions on the X, Y, Z axes by comparing the cubes around the entity. Because player entities and enemy entities
 *  are around 2 cubes tall, we do comparisons with the cubes that is next to the bounding box's lower point and upper point, basically
 *  the 2 cubes that are on the front or side.
 *
 *  If a collision happens, the rigid body's velocity vector is modified on the corresponding axis to 0
 */
void PhysicsSystem::handleCollision(RigidBody* rigidBody, Transform* transform, BoxCollider* boxCollider, Vector3f& acceleration) {

}




