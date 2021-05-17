//
// Created by Viktor on 13.3.2021 г..
//

#include "include/box_collider.h"

BoxCollider::BoxCollider() : m_dimensions(Vector3f(1, 1, 1)) {

}

BoxCollider::BoxCollider(const Vector3f dimensions) : m_dimensions(dimensions) {

}

void BoxCollider::update(const Vector3f& position) {
	m_boundingBox.min = position;
	m_boundingBox.max = position + m_dimensions;
}

void BoxCollider::updateInverse(const Vector3f& position) {
	m_boundingBox.min = position - m_dimensions;
	m_boundingBox.max = position;
}

bool BoxCollider::intersectsWith(const BoxCollider* o) const {
	return (m_boundingBox.min.x <= o->m_boundingBox.max.x && o->m_boundingBox.min.x <= m_boundingBox.max.x) &&
	       (m_boundingBox.min.y <= o->m_boundingBox.max.y && o->m_boundingBox.min.y <= m_boundingBox.max.y) &&
	       (m_boundingBox.min.z <= o->m_boundingBox.max.z && o->m_boundingBox.min.z <= m_boundingBox.max.z) ||
			(o->m_boundingBox.min.x <= m_boundingBox.max.x && m_boundingBox.min.x <= o->m_boundingBox.max.x) &&
			(o->m_boundingBox.min.y <= m_boundingBox.max.y && m_boundingBox.min.y <= o->m_boundingBox.max.y) &&
			(o->m_boundingBox.min.z <= m_boundingBox.max.z && m_boundingBox.min.z <= o->m_boundingBox.max.z);
}









