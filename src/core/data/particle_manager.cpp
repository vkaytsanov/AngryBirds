#include "include/particle_manager.h"

ParticleManager::ParticleManager() {
	initializeParticleUvs();
}

void ParticleManager::initializeParticleUvs() {
	m_particles[RedBirdFeathers] = TextureRegion(AssetManager::getInstance().getSprite("all-in-one"), 246, 965, 13, 31);
}


const TextureRegion ParticleManager::getParticle(ParticleType type) const {
	return m_particles[type];
}

ParticleManager& ParticleManager::getInstance() {
	static ParticleManager manager;
	return manager;
}
