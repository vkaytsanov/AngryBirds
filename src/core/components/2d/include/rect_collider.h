#pragma once
#include "entityx/Entity.h"
#include "utils/geometry/include/vector2.h"

struct BoundingRect {
	Vector2f min;
	Vector2f max;
};

class RectCollider : public entityx::Component<RectCollider>{
private:
	BoundingRect m_boundingRect;
	Vector2f m_dimensions;
public:
	RectCollider();
	RectCollider(const Vector2f dimensions);
	void update(const Vector2f& position);
	void updateInverse(const Vector2f& position);
	bool intersectsWith(const RectCollider* other) const;
};
