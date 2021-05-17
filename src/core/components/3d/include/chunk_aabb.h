//
// Created by Viktor on 7.3.2021 г..
//

#ifndef CHUNK_AABB_H
#define CHUNK_AABB_H


#include "../../include/transform.h"
#include "../../../../lib/entityx/entityx.h"

class ChunkAABB : public entityx::Component<ChunkAABB>{
private:
	Vector3f m_dimensions;
	Vector3f m_position;
public:
	ChunkAABB(Vector3f dimensions, Vector3f position);
	Vector3f getNegativeFarPoint(const Vector3f& normal);
	Vector3f getPositiveFarPoint(const Vector3f& normal);

};


#endif //CHUNK_AABB_H
