//
// Created by Viktor on 2.3.2021 г..
//

#include "include/frustum.h"



float Plane::distanceToPoint(Vector3f point) {
	return point.dot(m_normal) + m_distanceToOrigin;
}

void Frustum::update(Matrix4f* combined) {
	m_planes[PlaneType::NearPlane].m_normal.x = combined->a[A03] + combined->a[A02];
	m_planes[PlaneType::NearPlane].m_normal.y = combined->a[A13] + combined->a[A12];
	m_planes[PlaneType::NearPlane].m_normal.z = combined->a[A23] + combined->a[A22];
	m_planes[PlaneType::NearPlane].m_distanceToOrigin = combined->a[A33] + combined->a[A32];

	m_planes[PlaneType::FarPlane].m_normal.x = combined->a[A03] - combined->a[A02];
	m_planes[PlaneType::FarPlane].m_normal.y = combined->a[A13] - combined->a[A12];
	m_planes[PlaneType::FarPlane].m_normal.z = combined->a[A23] - combined->a[A22];
	m_planes[PlaneType::FarPlane].m_distanceToOrigin = combined->a[A33] - combined->a[A32];

	m_planes[PlaneType::TopPlane].m_normal.x = combined->a[A03] - combined->a[A01];
	m_planes[PlaneType::TopPlane].m_normal.y = combined->a[A13] - combined->a[A11];
	m_planes[PlaneType::TopPlane].m_normal.z = combined->a[A23] - combined->a[A21];
	m_planes[PlaneType::TopPlane].m_distanceToOrigin = combined->a[A33] - combined->a[A31];

	m_planes[PlaneType::BottomPlane].m_normal.x = combined->a[A03] + combined->a[A01];
	m_planes[PlaneType::BottomPlane].m_normal.y = combined->a[A13] + combined->a[A11];
	m_planes[PlaneType::BottomPlane].m_normal.z = combined->a[A23] + combined->a[A21];
	m_planes[PlaneType::BottomPlane].m_distanceToOrigin = combined->a[A33] + combined->a[A31];

	m_planes[PlaneType::LeftPlane].m_normal.x = combined->a[A03] + combined->a[A00];
	m_planes[PlaneType::LeftPlane].m_normal.y = combined->a[A13] + combined->a[A10];
	m_planes[PlaneType::LeftPlane].m_normal.z = combined->a[A23] + combined->a[A20];
	m_planes[PlaneType::LeftPlane].m_distanceToOrigin = combined->a[A33] + combined->a[A30];

	m_planes[PlaneType::RightPlane].m_normal.x = combined->a[A03] - combined->a[A00];
	m_planes[PlaneType::RightPlane].m_normal.y = combined->a[A13] - combined->a[A10];
	m_planes[PlaneType::RightPlane].m_normal.z = combined->a[A23] - combined->a[A20];
	m_planes[PlaneType::RightPlane].m_distanceToOrigin = combined->a[A33] - combined->a[A30];

	for(auto& plane: m_planes){
		float length = plane.m_normal.length();
		plane.m_normal /= length;
		plane.m_distanceToOrigin /= length;

	}
}

bool Frustum::boxInFrustum(ChunkAABB* box) {
	for(auto& plane : m_planes){
		if(plane.distanceToPoint(box->getPositiveFarPoint(plane.m_normal)) < 0){
			return false;
		}
	}
	return true;
}
