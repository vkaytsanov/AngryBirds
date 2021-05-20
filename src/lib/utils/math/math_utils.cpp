//
// Created by Viktor on 26.12.2020 г..
//

#include "include/math_utils.h"
#include <cassert>
#include <cmath>

namespace MathUtils {
	float toRadians(float degree) {
		return degree * (PI / 180);
	}

	b2Vec2 clamp(b2Vec2 val, const b2Vec2& min, const b2Vec2 max)  {
		if(val.x < min.x) val.x = min.x;
		else if(val.x > max.x) val.x = max.x;
		
		if(val.y < min.y) val.y = min.y;
		else if(val.y > max.y) val.y = max.y;

		return val;
	}
}
