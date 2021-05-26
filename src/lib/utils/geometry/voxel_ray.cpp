//
// Created by Viktor on 19.3.2021 г..
//

#include "include/voxel_ray.h"

VoxelRay::VoxelRay(const Vector3f& start, const Vector3f& direction) :m_direction(direction) {
	m_step.x = (direction.x >= 0) ? 1 : -1;
	m_step.y = (direction.y >= 0) ? 1 : -1;
	m_step.z = (direction.z >= 0) ? 1 : -1;

	Vector3f cubePos = Vector3f::floor(start);
	Vector3f nextCubePos = Vector3f(cubePos.x + m_step.x, cubePos.y + m_step.y, cubePos.z + m_step.z);

	m_tMax.x = (direction.x != 0) ? (nextCubePos.x - start.x) / direction.x : FLT_MAX; //
	m_tMax.y = (direction.y != 0) ? (nextCubePos.y - start.y) / direction.y : FLT_MAX; //
	m_tMax.z = (direction.z != 0) ? (nextCubePos.z - start.z) / direction.z : FLT_MAX; //

	m_tDelta.x = (direction.x != 0) ? 1 / direction.x * m_step.x : FLT_MAX;
	m_tDelta.y = (direction.y != 0) ? 1 / direction.y * m_step.y : FLT_MAX;
	m_tDelta.z = (direction.z != 0) ? 1 / direction.z * m_step.z : FLT_MAX;

	m_endPoint = start;
}

void VoxelRay::step() {
	if (m_tMax.x < m_tMax.y) {
		if (m_tMax.x < m_tMax.z) {
			m_endPoint.x -= m_step.x;
			m_tMax.x += m_tDelta.x;
		}
		else {
			m_endPoint.z -= m_step.z;
			m_tMax.z += m_tDelta.z;
		}
	}
	else if (m_tMax.y < m_tMax.z) {
		m_endPoint.y -= m_step.y;
		m_tMax.y += m_tDelta.y;
	}
	else {
		m_endPoint.z -= m_step.z;
		m_tMax.z += m_tDelta.z;
	}
}

Vector3f VoxelRay::getEndPoint() const {
	return m_endPoint;
}

void VoxelRay::stepBack() {
	if (m_tMax.x > m_tMax.y) {
		if (m_tMax.x > m_tMax.z) {
			m_endPoint.x += m_step.x;
			m_tMax.x -= m_tDelta.x;
		}
		else {
			m_endPoint.z += m_step.z;
			m_tMax.z -= m_tDelta.z;
		}
	}
	else if (m_tMax.y > m_tMax.z) {
		m_endPoint.y += m_step.y;
		m_tMax.y -= m_tDelta.y;
	}
	else {
		m_endPoint.z += m_step.z;
		m_tMax.z -= m_tDelta.z;
	}
}

Vector3f VoxelRay::getNormal() {
	if(m_tMax.x < m_tMax.y){
		if(m_tMax.x < m_tMax.z){
			return Vector3f(1 * m_step.x, 0, 0);
		}
		return Vector3f(0, 0, 1 * m_step.z);
	}
	else if(m_tMax.y < m_tMax.z){
		return Vector3f(0, 1 * m_step.y, 0);
	}
	return Vector3f(0, 0, 1 * m_step.z);

}
