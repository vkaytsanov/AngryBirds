//
// Created by Viktor on 11.3.2021 г..
//
#include <algorithm>
#include "include/transform.h"

Transform::Transform(const Vector3f& position) : position(position){}

void Transform::translate(const float x, const float y, const float z) {
	position.x += x;
	position.y += y;
	position.z += z;

	hasChanged = true;
}

void Transform::translate(const Vector3f& vec) {
	position += vec;

	hasChanged = true;
}

void Transform::rotate(const float roll, const float pitch, const float yaw) {
	rotation.x += roll;
	rotation.y += pitch;
	rotation.z += yaw;

	hasChanged = true;
}

void Transform::rotate(const Vector3f& vec) {
	eulerAngles += vec;

	hasChanged = true;
}

void Transform::rotateClampX(const Vector3f& vec, const float value) {
	eulerAngles += vec;
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201'703L) || __cplusplus >= 201'703L)
	eulerAngles.x = std::clamp(eulerAngles.x, -value, value);
#else
	if(eulerAngles.x < -value) eulerAngles.x = -value;
	else if(eulerAngles.x > value) eulerAngles.x = value;
#endif
	hasChanged = true;
}
