//
// Created by Viktor on 4.3.2021 г..
//

#ifndef TRANSFORM_H
#define TRANSFORM_H


#include "../../../lib/utils/geometry/include/vector3.h"
#include "../../../lib/utils/geometry/include/matrix4.h"



struct Transform {
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

	Transform(){}
	Transform(const Vector3f& position) : position(position){}

	void translate(const float x, const float y, const float z);
	void translate(const Vector3f& vec);
	void rotate(const float roll, const float pitch, const float yaw);
	void rotate(const Vector3f& vec);
	void rotateClampX(const Vector3f& vec, const float value);


};


#endif //TRANSFORM_H
