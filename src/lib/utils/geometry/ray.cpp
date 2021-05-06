//
// Created by Viktor on 5.3.2021 г..
//

#include <cmath>
#include "include/ray.h"

#if ((defined(_MSVC_LANG) && _MSVC_LANG < 201'703L) || __cplusplus < 201'703L)
#define FLT_MAX 3.4028234664e+38
#endif


Ray::Ray(const Vector3f& start, const Vector3f& direction) : m_startPoint(start),
                                                             m_endPoint(start),
                                                             m_direction(direction) {
	m_sign.x = (direction.x > 0) ? 1 : -1;
	m_sign.y = (direction.y > 0) ? 1 : -1;
	m_sign.z = (direction.z > 0) ? 1 : -1;

	Vector3f cubePos = Vector3f::floor(start);
	Vector3f nextCubePos = Vector3f(cubePos.x + m_sign.x, cubePos.y + m_sign.y, cubePos.z + m_sign.z);

	m_tVec.x = (direction.x != 0) ? (nextCubePos.x - start.x) / direction.x : FLT_MAX;
	m_tVec.y = (direction.y != 0) ? (nextCubePos.y - start.y) / direction.y : FLT_MAX;
	m_tVec.z = (direction.z != 0) ? (nextCubePos.z - start.z) / direction.z : FLT_MAX;

	m_minT = std::min(m_tVec.x, std::min(m_tVec.y, m_tVec.z));

}

void Ray::step() {
	m_endPoint -= m_direction * (m_minT + 0.001f);
}

Vector3f Ray::getEndPoint() {
	return m_endPoint;
}


float Ray::getLength() {
	return m_startPoint.distance(m_endPoint);
}

Vector3f Ray::getNormal() const {
	return Vector3f(static_cast<float>((m_minT == m_tVec.x)) * m_sign.x + 0.001f,
	                static_cast<float>((m_minT == m_tVec.y)) * m_sign.y + 0.001f,
	                static_cast<float>((m_minT == m_tVec.z)) * m_sign.z + 0.001f);
}
