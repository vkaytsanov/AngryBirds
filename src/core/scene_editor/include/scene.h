#pragma once
#include <string>

#include "entityx/Entity.h"

class Scene {
private:
	const std::string SCENES_PATH = "scenes/";
public:
	std::string m_fileName;
	Scene() = default;
	Scene(std::string name);
	void load(entityx::EntityManager* entities);
	void save(entityx::EntityManager* entities);

};
