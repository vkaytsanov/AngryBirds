#pragma once
#include "entityx/Entity.h"
#include "../components/include/bird.h"


#include "box2d-emscripten/Common/b2Math.h"

/* Event that makes all the pigs laugh and spawns bird feather particles */
struct TheBirdIsGone : public entityx::Event<TheBirdIsGone>{
	BirdType birdType = Undefined;
	b2Vec2 position = b2Vec2(0, 0);
	
	TheBirdIsGone() = default;
	TheBirdIsGone(BirdType type, const b2Vec2& position) : birdType(type), position(position){}
	
};
