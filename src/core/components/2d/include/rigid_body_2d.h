#pragma once
#include "entityx/Entity.h"
#include "../../../data/include/box2d_database.h"

struct RigidBody2D : public entityx::Component<RigidBody2D>{
	b2Body* body;
	BodyInfo bodyInfo;
	explicit RigidBody2D(const BodyInfo& bodyInfo);
	
	template<typename Archive>
	void serialize(Archive& archive);
};

template <typename Archive>
void RigidBody2D::serialize(Archive& archive) {
	archive(bodyInfo);
}
