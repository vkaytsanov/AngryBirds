
#include "include/rigid_body.h"


void RigidBody::addForce(const Vector3f& force) {
	m_velocity += force * Lib::graphics->getDeltaTime() / m_mass;
	m_isActive = true;
}

void RigidBody::addForceImpulse(const Vector3f& force) {
	m_velocity += force / m_mass;
	m_isActive = true;
}
