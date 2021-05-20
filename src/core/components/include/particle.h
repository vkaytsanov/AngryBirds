//
// Created by Viktor on 18.3.2021 г..
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include "../../../lib/utils/geometry/include/vector3.h"
#include "../../../lib/utils/geometry/include/vector2.h"



struct ParticleVertex{
	Vector2f vertices;
	Vector2f uvs;
};

struct ParticleInstancedVertex{
	Vector2f position;
	Vector2f size;
};

struct Particle{
	Vector2f position;
	Vector2f velocity;
	Vector2f size = Vector2f(5.0f, 5.0f);
	float lifetime = 1.0f;
	float elapsedTime = 0.0f;
	bool isAlive() const;
	void update(float dt);
	Particle(Vector2f velocity) : velocity(velocity){}
	Particle() = default;
};




#endif //PARTICLE_H
