#pragma once

#include <box2d/b2_circle_shape.h>

#include "entityx/Entity.h"

class CircleCollider : public entityx::Component<CircleCollider>{
private:
	b2CircleShape m_bounds;
public:
	CircleCollider(float radius);
};
