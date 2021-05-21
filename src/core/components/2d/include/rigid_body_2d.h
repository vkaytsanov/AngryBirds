#pragma once
#include "entityx/Entity.h"
#include "../../../data/include/box2d_database.h"

struct RigidBody2D : public entityx::Component<RigidBody2D>{
	// to be initialized from #PhysicsSystem2D
	b2Body* body;
	BodyInfo bodyInfo;
	explicit RigidBody2D(const BodyInfo& bodyInfo);
	
	template<typename Archive>
	void save(Archive& archive);
	
	template<typename Archive>
	void load(Archive& archive);
};


template <typename Archive>
void RigidBody2D::save(Archive& archive) {
	archive(bodyInfo);
}

template <typename Archive>
void RigidBody2D::load(Archive& archive) {
	// loading only the prefab type
	archive(bodyInfo);
	// loading the real body info
	bodyInfo = Box2dDatabase::getInstance().fromTypeToBody(bodyInfo.entityType);
}
