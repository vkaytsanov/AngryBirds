//
// Created by Viktor on 5.3.2021 г..
//

#ifndef RAY_H
#define RAY_H


#include "vector3.h"

class Ray {
private:
	Vector3f m_startPoint;
	Vector3f m_endPoint;
	Vector3f m_sign;
	Vector3f m_tVec;
	float m_minT;
	Vector3f m_direction;
public:
	Ray() = default;
	Ray(const Vector3f& start, const Vector3f& direction);
	void step();
	Vector3f getEndPoint();
	float getLength();
	Vector3f getNormal() const;

};


#endif //RAY_H
