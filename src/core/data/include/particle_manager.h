#pragma once

#include "utils/include/texture_region.h"

enum ParticleType : uint32_t{
	RedBirdFeathers,
	MAX_NUMBER_OF_PARTICLES
};


class ParticleManager {
private:
	std::array<TextureRegion, MAX_NUMBER_OF_PARTICLES> m_particles;
private:
	void initializeParticleUvs();
public:
	ParticleManager();
	const TextureRegion getParticle(ParticleType type) const;
	static ParticleManager& getInstance();
};
