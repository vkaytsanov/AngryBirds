//
// Created by Viktor on 19.3.2021 г..
//

#ifndef VOXEL_RAY_H
#define VOXEL_RAY_H

#include "vector3.h"

/** Based on the DDA Voxel RayCast Algorithm */
class VoxelRay {
private:
	Vector3f m_endPoint;
	Vector3f m_step;
	Vector3f m_tDelta;
	Vector3f m_tMax;
	Vector3f m_direction;
public:
	VoxelRay() = default;
	VoxelRay(const Vector3f& start, const Vector3f& direction);
	void step();
	void stepBack();
	Vector3f getNormal();
	Vector3f getEndPoint() const;
};


#endif //VOXEL_RAY_H
