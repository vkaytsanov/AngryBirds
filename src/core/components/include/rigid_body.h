//
// Created by Viktor on 13.3.2021 г..
//

#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include "../../../lib/entityx/entityx.h"
#include "../../../lib/utils/geometry/include/vector3.h"

class RigidBody : public entityx::Component<RigidBody>{
	friend class PhysicsSystem;
private:
	/** if it should be updated in the loop */
	bool m_isActive = true;
public:
	bool m_useGravity = true;
	bool m_isGrounded = false;
	/** mass in kilos */
	float m_mass = 1.0f;
	/** friction */
	float m_drag = 5.0f;
	Vector3f m_velocity;
	void addForce(const Vector3f& force);
	void addForceImpulse(const Vector3f& force);

	template<typename Archive>
	void serialize(Archive& archive) {
		archive(m_useGravity);
	}

};


#endif //RIGID_BODY_H
