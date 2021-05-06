//
// Created by Viktor on 17.2.2021 г..
//

#ifndef VERTEX_H
#define VERTEX_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <SDL/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "../../geometry/include/vector3.h"
#include "../../geometry/include/vector2.h"

struct Vertex {
	Vector3f position;
	Vector2f uvs;
	uint8_t lightningLevel;
};


#endif //VERTEX_H
