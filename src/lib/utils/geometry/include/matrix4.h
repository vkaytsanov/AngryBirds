//
// Created by Viktor on 21.12.2020 г..
//

#ifndef MATRIX4_H
#define MATRIX4_H


#include <iostream>
#include "vector3.h"
#include "quaternion.h"

#define A00 0
#define A01 1
#define A02 2
#define A03 3
#define A10 4
#define A11 5
#define A12 6
#define A13 7
#define A20 8
#define A21 9
#define A22 10
#define A23 11
#define A30 12
#define A31 13
#define A32 14
#define A33 15

/**
 *  Column major matrix
 *  [ A00 ] [ A01 ] [ A02 ] [ A03 ]	x
 *  [ A10 ] [ A11 ] [ A12 ] [ A13 ]	y
 *  [ A20 ] [ A21 ] [ A22 ] [ A23 ]	z
 *  [ A30 ] [ A31 ] [ A32 ] [ A33 ]	w
 *
 *  A00, A10, A20 - Right Vector
 *  A01, A11, A21 - Up Vector
 *  A02, A12, A22 - Forward Vector
 *
 *
 */

template<typename T>
class Matrix4 {
public:
	T a[16];

	Matrix4() {
		identity();
	}

	Matrix4(Matrix4<T>* mat) {
		for (int i = 0; i < 16; i++) {
			a[i] = mat->a[i];
		}
	}

	Matrix4(T other[16]) {
		for (int i = 0; i < 16; i++) {
			a[i] = other[i];
		}
	}

	void identity();
	void zerofy();
	void setToOrthogonal(T left, T right, T bottom, T top, T near, T far);
	Matrix4<T> setToProjection(const T fov, const T near, const T far, const T aspectRatio);
	Matrix4<T>&
	setToLookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up = Vector3<T>(0, 1, 0));
	Matrix4<T> setToTransform(const Vector3<T>& position, const Quaternion<T>& rotation);
	Matrix4<T>& setForTranslation(T x, T y, T z);
	Matrix4<T>& setForTranslation(const Vector3<T>& vec);
	Matrix4<T> noTranslation();
	Matrix4<T> angleToMatrix(const Vector3<T>& angle);
	Matrix4<T> fromQuaternion(const Quaternion<T>& q);
	Matrix4<T> transpose();

	T& operator[](int idx);
	Matrix4<T> operator*(const Matrix4<T>& mat);
	Matrix4<T>& operator=(const Matrix4<T>& other);

	void debug();
};

/**  @link https://docs.microsoft.com/en-us/windows/win32/opengl/glortho */
template<typename T>
void Matrix4<T>::setToOrthogonal(T left, T right, T bottom, T top, T near, T far) {
// following the picture and formulas on the Microsoft's OpenGL page - glOrtho() function
	identity();
	a[A00] = 2 / (right - left);
	a[A11] = 2 / (top - bottom);
	a[A22] = -2 / (far - near);

	a[A03] = -(right + left) / (right - left);
	a[A13] = -(top + bottom) / (top - bottom);
	a[A23] = -(far + near) / (far - near);
}

template<typename T>
void Matrix4<T>::identity() {
	// Create identity matrix with 1's on the diagonal and 0's everywhere else
	a[A00] = 1;
	a[A01] = 0;
	a[A02] = 0;
	a[A03] = 0;
	a[A10] = 0;
	a[A11] = 1;
	a[A12] = 0;
	a[A13] = 0;
	a[A20] = 0;
	a[A21] = 0;
	a[A22] = 1;
	a[A23] = 0;
	a[A30] = 0;
	a[A31] = 0;
	a[A32] = 0;
	a[A33] = 1;
}

/** @link https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluLookAt.xml */
template<typename T>
Matrix4<T>& Matrix4<T>::setToLookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up) {
	Vector3<T> forward = (center - eye).normalize();
	Vector3<T> right = (forward.cross(up)).normalize();
	Vector3<T> u = right.cross(forward);

	identity();
	a[A00] = right.x;
	a[A10] = right.y;
	a[A20] = right.z;
	a[A01] = u.x;
	a[A11] = u.y;
	a[A21] = u.z;
	a[A02] = -forward.x;
	a[A12] = -forward.y;
	a[A22] = -forward.z;
	a[A30] = -right.dot(eye);
	a[A31] = -u.dot(eye);
	a[A32] = forward.dot(eye);


	return *this;
}


template<typename T>
Matrix4<T>& Matrix4<T>::setForTranslation(T x, T y, T z) {
	a[A30] = x;
	a[A31] = y;
	a[A32] = z;
	return *this;
}

template<typename T>
Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& mat) {
	Matrix4<T> result;
	result[A00] = mat.a[A00] * a[A00] + mat.a[A01] * a[A10] + mat.a[A02] * a[A20] + mat.a[A03] * a[A30];
	result[A01] = mat.a[A00] * a[A01] + mat.a[A01] * a[A11] + mat.a[A02] * a[A21] + mat.a[A03] * a[A31];
	result[A02] = mat.a[A00] * a[A02] + mat.a[A01] * a[A12] + mat.a[A02] * a[A22] + mat.a[A03] * a[A32];
	result[A03] = mat.a[A00] * a[A03] + mat.a[A01] * a[A13] + mat.a[A02] * a[A23] + mat.a[A03] * a[A33];
	result[A10] = mat.a[A10] * a[A00] + mat.a[A11] * a[A10] + mat.a[A12] * a[A20] + mat.a[A13] * a[A30];
	result[A11] = mat.a[A10] * a[A01] + mat.a[A11] * a[A11] + mat.a[A12] * a[A21] + mat.a[A13] * a[A31];
	result[A12] = mat.a[A10] * a[A02] + mat.a[A11] * a[A12] + mat.a[A12] * a[A22] + mat.a[A13] * a[A32];
	result[A13] = mat.a[A10] * a[A03] + mat.a[A11] * a[A13] + mat.a[A12] * a[A23] + mat.a[A13] * a[A33];
	result[A20] = mat.a[A20] * a[A00] + mat.a[A21] * a[A10] + mat.a[A22] * a[A20] + mat.a[A23] * a[A30];
	result[A21] = mat.a[A20] * a[A01] + mat.a[A21] * a[A11] + mat.a[A22] * a[A21] + mat.a[A23] * a[A31];
	result[A22] = mat.a[A20] * a[A02] + mat.a[A21] * a[A12] + mat.a[A22] * a[A22] + mat.a[A23] * a[A32];
	result[A23] = mat.a[A20] * a[A03] + mat.a[A21] * a[A13] + mat.a[A22] * a[A23] + mat.a[A23] * a[A33];
	result[A30] = mat.a[A30] * a[A00] + mat.a[A31] * a[A10] + mat.a[A32] * a[A20] + mat.a[A33] * a[A30];
	result[A31] = mat.a[A30] * a[A01] + mat.a[A31] * a[A11] + mat.a[A32] * a[A21] + mat.a[A33] * a[A31];
	result[A32] = mat.a[A30] * a[A02] + mat.a[A31] * a[A12] + mat.a[A32] * a[A22] + mat.a[A33] * a[A32];
	result[A33] = mat.a[A30] * a[A03] + mat.a[A31] * a[A13] + mat.a[A32] * a[A23] + mat.a[A33] * a[A33];
	return result;
}

template<typename T>
void Matrix4<T>::zerofy() {
	for (int i = 0; i < 16; i++) {
		a[i] = 0;
	}
}

template<typename T>
Matrix4<T>& Matrix4<T>::setForTranslation(const Vector3<T>& vec) {
	a[A30] = vec.x;
	a[A31] = vec.y;
	a[A32] = vec.z;
	return *this;
}

template<typename T>
Matrix4<T> Matrix4<T>::noTranslation() {
	Matrix4<T> mat(this);
	mat.a[A30] = 0;
	mat.a[A31] = 0;
	mat.a[A32] = 0;
	mat.a[A33] = 1;
	return mat;
}

template<typename T>
Matrix4<T>& Matrix4<T>::operator=(const Matrix4<T>& other) {
	if (this != &other) {
		for (int i = 0; i < 16; i++) {
			a[i] = other.a[i];
		}
	}
	return *this;
}

template<typename T>
T& Matrix4<T>::operator[](int idx) {
	return a[idx];
}

/** https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-m_projection-matrix/opengl-perspective-m_projection-matrix */
template<typename T>
Matrix4<T> Matrix4<T>::setToProjection(const T fov, const T near, const T far, const T aspectRatio) {
	const float tanHalfFovy = std::tan(fov / 2.f);

	zerofy();

	a[A00] = 1 / (aspectRatio * tanHalfFovy);
	a[A11] = 1 / (tanHalfFovy);
	a[A22] = -(far + near) / (far - near);
	a[A23] = -1;
	a[A32] = -(2 * far * near) / (far - near);

	return *this;
}

template<typename T>
void Matrix4<T>::debug() {
	std::cout << "----------------START OF DEBUG-------------" << std::endl;
	std::cout << "\t[" << a[A00] << "]""\t[" << a[A01] << "]""\t[" << a[A02] << "]""\t[" << a[A03] << "]"
	          << std::endl;
	std::cout << "\t[" << a[A10] << "]""\t[" << a[A11] << "]""\t[" << a[A12] << "]""\t[" << a[A13] << "]"
	          << std::endl;
	std::cout << "\t[" << a[A20] << "]""\t[" << a[A21] << "]""\t[" << a[A22] << "]""\t[" << a[A23] << "]"
	          << std::endl;
	std::cout << "\t[" << a[A30] << "]""\t[" << a[A31] << "]""\t[" << a[A32] << "]""\t[" << a[A33] << "]"
	          << std::endl;
	std::cout << "------------------END OF DEBUG-------------" << std::endl;
}

template<typename T>
Matrix4<T> Matrix4<T>::angleToMatrix(const Vector3<T>& angle) {
	return Matrix4<T>().fromQuaternion(Quaternion<T>().fromEulers(angle));
}

template<typename T>
Matrix4<T> Matrix4<T>::fromQuaternion(const Quaternion<T>& q) {
	Matrix4<T> result;

	T qxx = q.x * q.x;
	T qyy = q.y * q.y;
	T qzz = q.z * q.z;
	T qxz = q.x * q.z;
	T qxy = q.x * q.y;
	T qyz = q.y * q.z;
	T qwx = q.w * q.x;
	T qwy = q.w * q.y;
	T qwz = q.w * q.z;


	result[A00] = 1 - 2 * (qyy + qzz);
	result[A01] = 2 * (qxy + qwz);
	result[A02] = 2 * (qxz - qwy);
	result[A10] = 2 * (qxy - qwz);
	result[A11] = 1 - 2 * (qxx + qzz);
	result[A12] = 2 * (qyz + qwx);
	result[A20] = 2 * (qxz + qwy);
	result[A21] = 2 * (qyz - qwx);
	result[A22] = 1 - 2 * (qxx + qyy);

	return result;
}

template<typename T>
Matrix4<T> Matrix4<T>::setToTransform(const Vector3<T>& position, const Quaternion<T>& rotation) {
	// TODO FIX THIS FUNCTION TO RETURN BY REFERENCE BY CHANGING THIS MATRIX'S CONTENTS
	return Matrix4<T>().fromQuaternion(rotation) * Matrix4<T>().setForTranslation(position * (-1));
}

template<typename T>
Matrix4<T> Matrix4<T>::transpose() {
	return Matrix4<T>(a[A00], a[A10], a[A20], a[A30],
	                  a[A01], a[A11], a[A21], a[A31],
	                  a[A02], a[A12], a[A22], a[A32],
	                  a[A03], a[A13], a[A23], a[A33]);
}


typedef Matrix4<float> Matrix4f;
typedef Matrix4<int> Matrix4i;

#endif //MATRIX4_H
