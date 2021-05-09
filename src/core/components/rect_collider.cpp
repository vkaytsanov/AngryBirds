#include "include/rect_collider.h"

RectCollider::RectCollider() : m_dimensions(Vector2f(1, 1)){
}

RectCollider::RectCollider(const Vector2f dimensions) : m_dimensions(dimensions){
}

void RectCollider::update(const Vector2f& position) {
	m_boundingRect.min = position;
	m_boundingRect.max = position + m_dimensions;
	
}

void RectCollider::updateInverse(const Vector2f& position) {
}

bool RectCollider::intersectsWith(const RectCollider* other) const {
	return false;
}
