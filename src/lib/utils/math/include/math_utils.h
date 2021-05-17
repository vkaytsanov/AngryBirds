//
// Created by Viktor on 26.12.2020 г..
//

#ifndef MATH_UTILS_H
#define MATH_UTILS_H


namespace MathUtils {
	const float EPS = 0.000001f;
	const float PI = 3.14159265359f;
	const float DEG2RAD = (PI / 180);
	const float RAD2DEG = (180 / PI);

	float toRadians(float degree);
	float bilerp(float bottomLeft, float topLeft, float bottomRight, float topRight,
	             float xMin,       float xMax,
	             float yMin,       float yMax,
	             float xToCalc,    float yToCalc);

}


#endif //MATH_UTILS_H
