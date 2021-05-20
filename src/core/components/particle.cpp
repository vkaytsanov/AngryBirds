//
// Created by Viktor on 18.3.2021 г..
//

#include "include/particle.h"


bool Particle::isAlive() const {
	return elapsedTime < lifetime;
}

void Particle::update(float dt) {
	elapsedTime += dt;
	position += velocity * dt;
}
