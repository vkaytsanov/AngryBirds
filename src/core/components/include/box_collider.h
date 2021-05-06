//
// Created by Viktor on 13.3.2021 г..
//

#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include <array>
#include "transform.h"
#include "../../../lib/entityx/entityx.h"

struct BoundingBox{
	Vector3f min;
	Vector3f max;

};

class BoxCollider : public entityx::Component<BoxCollider>{
private:
public:
	Vector3f m_dimensions;
	BoundingBox m_boundingBox;
	BoxCollider();
	BoxCollider(const Vector3f dimensions);
	void update(const Vector3f& position);
	void updateInverse(const Vector3f& position);
	bool intersectsWith(const BoxCollider* other) const;
};


#endif //BOX_COLLIDER_H
