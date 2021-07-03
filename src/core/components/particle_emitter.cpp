//
// Created by Viktor on 23.3.2021 г..
//

#include <array>

#include "include/particle_emitter.h"
#include "../data/include/particle_manager.h"

#if defined(__EMSCRIPTEN__) || defined(EMSCRIPTEN_DEVELOPMENT)
GLint ParticleEmitter::m_verticesLocation = 0;
GLint ParticleEmitter::m_uvLocation = 0;
GLint ParticleEmitter::m_positionLocation = 0;
GLint ParticleEmitter::m_sizeLocation = 0;
#endif

/** Draws particles in a single draw call at @param emittingPosition, using 2 Vertex Buffers.
 * One is for the constant vertices and uvs that are shared between all the particles,
 * and one vertex buffer that has the position and size of each instanced particle */
ParticleEmitter::ParticleEmitter(ParticleType type) : particleType(type) {
	VertexBuffer vbo;
	vao.bind();
	vbo.bind();
	
#if defined(__EMSCRIPTEN__) || defined(EMSCRIPTEN_DEVELOPMENT)
	vbo.vertexAttribPointer(m_verticesLocation, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex),
		(void*)(offsetof(ParticleVertex, vertices)));
	vbo.vertexAttribPointer(m_uvLocation, 2, GL_FLOAT, GL_TRUE, sizeof(ParticleVertex),
		(void*)(offsetof(ParticleVertex, uvs)));
#else
	vbo.vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleVertex),
	                        (void*)(offsetof(ParticleVertex, vertices)));
	vbo.vertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(ParticleVertex),
	                        (void*)(offsetof(ParticleVertex, uvs)));
#endif
	instancedVbo.bind();
#if defined(__EMSCRIPTEN__) || defined(EMSCRIPTEN_DEVELOPMENT)
	instancedVbo.vertexAttribPointer(m_positionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleInstancedVertex),
		(void*)(offsetof(ParticleInstancedVertex, position)));
	instancedVbo.vertexAttribPointer(m_sizeLocation, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleInstancedVertex),
		(void*)(offsetof(ParticleInstancedVertex, size)));
#else
	instancedVbo.vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleInstancedVertex),
	                                 (void*)(offsetof(ParticleInstancedVertex, position)));
	instancedVbo.vertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleInstancedVertex),
	                                 (void*)(offsetof(ParticleInstancedVertex, size)));
#endif
	instancedVbo.unbind();

	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices
	glVertexAttribDivisor(1, 0); // uvs : always reuse
	glVertexAttribDivisor(2, 1); // positions : one per quad
	glVertexAttribDivisor(3, 1); // sizes : one per quad

	
	unsigned int verticesCounter = 0;

	const TextureRegion& tR = ParticleManager::getInstance().getParticle(type);
	const float width = static_cast<float>(tR.getRegionWidth()) / 5.f;
	const float height = static_cast<float>(tR.getRegionHeight()) / 5.f;
	
	const float particleVertices[] = {
		-width, -height,
		width, -height,
		width, height,
		-width, height,
	};
	const std::array<float, 8> uvs = tR.getPackedUvs();

	std::array<ParticleVertex, 4> vertices;
	for (int i = 0; i < 4; i++) {
		ParticleVertex vertex;
		vertex.vertices = Vector2f(particleVertices[verticesCounter + i + 0],
		                           particleVertices[verticesCounter + i + 1]);
		vertex.uvs = Vector2f(uvs[verticesCounter + i + 0],
		                      uvs[verticesCounter + i + 1]);
		vertices[i] = vertex;
		verticesCounter += 1;
	}

	vbo.bind();
	vbo.bufferData(sizeof(ParticleVertex) * 4, &vertices[0], GL_STREAM_DRAW);
	vbo.unbind();
	vao.unbind();
}

void ParticleEmitter::update(float dt) {
	lifetime -= dt;
	int counter = 0;
	std::vector<float> particlesInstances(particles.size() * 4);
	// update the particles positions' buffer
	for (auto& particle : particles) {
		particle.update(dt);
		particlesInstances[counter + 0] = emittingPosition.x + particle.position.x;
		particlesInstances[counter + 1] = emittingPosition.y + particle.position.y;
		particlesInstances[counter + 2] = particle.size.x;
		particlesInstances[counter + 3] = particle.size.y;
		counter += 4;
	}

	instancedVbo.bind();
	instancedVbo.bufferData(particlesInstances.size() * sizeof(ParticleInstancedVertex), nullptr, GL_DYNAMIC_DRAW);
	instancedVbo.bufferSubData(0, particlesInstances.size() * sizeof(ParticleInstancedVertex), &particlesInstances[0]);
	instancedVbo.unbind();
}

void ParticleEmitter::setToExplosionEmitter() {
	// Creating a circle starting from pi counter clockwise
	particles.reserve(8);
	lifetime = 5.f;
	particles.emplace_back(Particle(Vector2f(2.0f, 0)));
	particles.emplace_back(Particle(Vector2f(1.5f, 1.5f)));
	particles.emplace_back(Particle(Vector2f(0, 2.0f)));
	particles.emplace_back(Particle(Vector2f(-1.5f, 1.5f)));
	particles.emplace_back(Particle(Vector2f(-2.0f, 0.0f)));
	particles.emplace_back(Particle(Vector2f(-1.5f, -1.5f)));
	particles.emplace_back(Particle(Vector2f(0.0f, -2.0f)));
	particles.emplace_back(Particle(Vector2f(1.5f, -1.5f)));

	for (auto& particle : particles) {
		particle.size = Vector2f(1, 1);
	}

}

bool ParticleEmitter::isAlive() const {
	return lifetime > 0.0f;
}
