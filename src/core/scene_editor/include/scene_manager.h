#pragma once
#include <vector>

#include "scene.h"

class SceneManager {
private:
	const std::string SCENES_PATH = "scenes/";
public:
	Scene* m_pCurrentScene;
	std::unordered_map<std::string, Scene> m_scenes;
public:
	SceneManager();
	Scene& getScene(const std::string& name);
	void changeScene(entityx::EntityManager* entityManager, const std::string& to);
	void createScene(entityx::EntityManager* entityManager, const std::string& name);
	void saveCurrentScene(entityx::EntityManager* entityManager);
};
