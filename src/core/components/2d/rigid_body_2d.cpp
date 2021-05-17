#include "include/rigid_body_2d.h"

RigidBody2D::RigidBody2D(const b2BodyDef& bodyDef, const b2FixtureDef& fixtureDef) : body(nullptr),
	bodyDef(bodyDef),
	fixtureDef(fixtureDef) {
}
