#pragma once
#include <array>

#include "entityx/Entity.h"

class PigsDB {
private:
	std::array<entityx::Entity, 4> m_templates;
public:
	PigsDB(entityx::EntityManager& entityManager);
};
