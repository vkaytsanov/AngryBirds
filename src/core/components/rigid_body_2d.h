#pragma once
#include "entityx/Entity.h"
#include "box2d/b2_body.h"

struct RigidBody2D : public entityx::Component<RigidBody2D>{
	b2Body* body;

	RigidBody2D(b2Shape* collider);
};
