//
// Created by Viktor on 23.3.2021 г..
//

#ifndef PARTICLE_EMITTER_H
#define PARTICLE_EMITTER_H


#include "../../../lib/entityx/entityx.h"
#include "../../../lib/utils/geometry/include/vector3.h"
#include "../../../lib/utils/geometry/include/vector2.h"
#include "../../../lib/utils/openGL/include/vertex_array.h"
#include "../../../lib/utils/openGL/include/vertex_buffer.h"
#include "../../data/include/particle_manager.h"
#include "particle.h"

struct ParticleEmitter : public entityx::Component<ParticleEmitter>{
#if defined(__EMSCRIPTEN__) || defined(EMSCRIPTEN_DEVELOPMENT)
	static GLint m_verticesLocation;
	static GLint m_uvLocation;
	static GLint m_positionLocation;
	static GLint m_sizeLocation;
#endif
	
	std::vector<Particle> particles;
	Vector3f emittingPosition;
	bool hasGravity = false;
	ParticleType particleType;
	float lifetime = 3.0f;
	VertexArray vao;
	VertexBuffer instancedVbo;

	ParticleEmitter() = default;
	ParticleEmitter(ParticleType type);
	void update(float dt);
	void setToExplosionEmitter();
	bool isAlive() const;

};


#endif //PARTICLE_EMITTER_H
