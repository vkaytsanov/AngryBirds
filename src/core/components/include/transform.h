//
// Created by Viktor on 4.3.2021 г..
//

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../../../lib/entityx/entityx.h"
#include "../../../lib/utils/geometry/include/vector3.h"
#include "../../../lib/utils/geometry/include/matrix4.h"



struct Transform : public entityx::Component<Transform>{
	Vector3f position;
	Vector3f eulerAngles;
	Vector3f scale = Vector3f(1, 1, 1);

	Quaternionf rotation;

	Vector3f right   = Vector3f(1, 0, 0);
	Vector3f up      = Vector3f(0, 1, 0);
	Vector3f forward = Vector3f(0, 0, 1);

	Matrix4f transformMatrix;

	// has changed since the last frame
	bool hasChanged = true;

	Transform() = default;
	Transform(const Vector3f& position);
	Transform(const Transform& other) = default;
	Transform(Transform&& other) = default;
	Transform& operator=(const Transform& other) = default;

	void translate(const float x, const float y, const float z);
	void translate(const Vector3f& vec);
	void rotate(const float roll, const float pitch, const float yaw);
	void rotate(const Vector3f& vec);
	void rotateClampX(const Vector3f& vec, const float value);
	
	template<typename Archive>
	inline void serialize(Archive& archive);
};

template <typename Archive>
void Transform::serialize(Archive& archive) {
	archive(position, eulerAngles, scale);
}


#endif //TRANSFORM_H
