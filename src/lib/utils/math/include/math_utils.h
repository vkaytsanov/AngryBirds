//
// Created by Viktor on 26.12.2020 г..
//

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#if !defined(__EMSCRIPTEN__)
#include "box2d/b2_math.h"
#else
#include "box2d-emscripten/Common/b2Math.h"
#endif


namespace MathUtils {
	const float EPS = 0.000001f;
	const float PI = 3.14159265359f;
	const float DEG2RAD = (PI / 180);
	const float RAD2DEG = (180 / PI);

	float toRadians(float degree);
	
	b2Vec2 clamp(b2Vec2 val, const b2Vec2& min, const b2Vec2 max);

}


#endif //MATH_UTILS_H
