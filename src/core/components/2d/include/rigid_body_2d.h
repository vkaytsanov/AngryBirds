#pragma once
#include "entityx/Entity.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"

struct RigidBody2D : public entityx::Component<RigidBody2D>{
	b2Body* body;
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	explicit RigidBody2D(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef);
};
