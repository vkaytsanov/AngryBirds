//
// Created by Viktor on 29.12.2020 г..
//

#ifndef QUATERNION_H
#define QUATERNION_H

#include "../../math/include/math_utils.h"
#include "../../../include/lib.h"

template<typename T>
class Vector3;

template<typename T>
class Quaternion {
public:
	T x;
	T y;
	T z;
	T w;

	Quaternion() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 1;
	}

	Quaternion(const T x, const T y, const T z) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = 1;
	}

	Quaternion(const T x, const T y, const T z, const T w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion<T> fromEulers(T roll, T pitch, T yaw) {
		return fromEulers({roll, pitch, yaw});
	}

	Quaternion<T> fromEulers(const Vector3<T>& angles) {
		Vector3<T> c = Vector3<T>(std::cos(angles.x * 0.5), std::cos(angles.y * 0.5), std::cos(angles.z * 0.5));
		Vector3<T> s = Vector3<T>(std::sin(angles.x * 0.5), std::sin(angles.y * 0.5), std::sin(angles.z * 0.5));

		Quaternion q;
		q.w = c.x * c.y * c.z + s.x * s.y * s.z;
		q.x = s.x * c.y * c.z - c.x * s.y * s.z;
		q.y = c.x * s.y * c.z + s.x * c.y * s.z;
		q.z = c.x * c.y * s.z - s.x * s.y * c.z;

		return q;
	}

	Quaternion<T> operator*(const Quaternion<T>& rhs) {
		Vector3<T> v1(x, y, z);
		Vector3<T> v2(rhs.x, rhs.y, rhs.z);

		Vector3<T> cross = v1.cross(v2);
		float dot = v1.dot(v2);
		Vector3<T> v3 = cross + (v2 * w) + (v1 * rhs.w);

		return Quaternion<T>(v3.x, v3.y, v3.z, w * rhs.w - dot);
	}

	Quaternion<T> conjugate() {
		return Quaternion(-x, -y, -z, w);
	}

	Quaternion<T> operator+(const Quaternion<T>& q) {
		return Quaternion<T>(x + q.x, y + q.y, z + q.z, w + q.w);
	}

	Quaternion<T> operator-(const Quaternion<T>& q) {
		return Quaternion<T>(x - q.x, y - q.y, z - q.z, w - q.w);
	}

	Quaternion<T> operator*(const Vector3<T>& vec) {
		return *this * Quaternion<T>(vec.x, vec.y, vec.z, 0);
	}

	Quaternion<T> operator*(const T& scale) {
		return Quaternion<T>(x * scale, y * scale, z * scale, w + scale);
	}

	Quaternion<T> operator/(const Quaternion<T>& q) {
		return Quaternion<T>(x / q.x, y / q.y, z / q.z, w / q.w);
	}

	Quaternion<T>& operator/=(const Quaternion<T>& q) {
		return Quaternion<T>(x / q.x, y / q.y, z / q.z, w / q.w);
	}


	Quaternion<T> identity() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 1;
		return *this;
	}

	/** Euclidean length */
	T length() {
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	/** Squared Euclidean length */
	T length2() {
		return x * x + y * y + z * z + w * w;
	}

	Quaternion<T> normalize() {
		float magnitude = length2();
		if (magnitude == 0.0f || magnitude == 1.0f) return *this;
		magnitude = std::sqrt(magnitude);
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		w /= magnitude;
		return *this;
	}

	/** returns the dot product |a . b| between two quaternions */
	float dot(const Quaternion<T>& q) {
		return (x * q.x + y * q.y + z * q.z + w * q.w);
	}

	static Quaternion<T> slerp(Quaternion<T>& q1, Quaternion<T>& q2, double alpha) {
		float dotproduct = q1.dot(q2);
		float theta, st, sut, sout, coeff1, coeff2;

		// algorithm adapted from Shoemake's paper
		alpha = alpha / 2.0;

		theta = (float) acos(dotproduct);
		if (theta < 0.0) theta = -theta;

		st = (float) sin(theta);
		sut = (float) sin(alpha * theta);
		sout = (float) sin((1 - alpha) * theta);
		coeff1 = sout / st;
		coeff2 = sut / st;

		return Quaternion<T>(coeff1 * q1.x + coeff2 * q2.x,
		                     coeff1 * q1.y + coeff2 * q2.y,
		                     coeff1 * q1.z + coeff2 * q2.z,
		                     coeff1 * q1.w + coeff2 * q2.w).normalize();
	}

	void debug(){
		Lib::app->log("quaternion", (std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + " " +
		                             std::to_string(w)).c_str());
	}

};

typedef Quaternion<float> Quaternionf;
typedef Quaternion<int> Quaternioni;


#endif //QUATERNION_H
