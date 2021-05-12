#include "include/scene_manager.h"
#include "utils/include/dirent.h"
#include "include/lib.h"

struct Transform;

SceneManager::SceneManager() : m_pCurrentScene(nullptr) {
	DIR* dir;
	if ((dir = opendir(SCENES_PATH.c_str())) != nullptr) {
		dirent* dirent;
		int c = 0;
		while ((dirent = readdir(dir)) != nullptr) {
			// skipping the directories, we need only files
			if (!strcmp(dirent->d_name, ".")) continue;
			if (!strcmp(dirent->d_name, "..")) continue;
			std::string name(dirent->d_name);
			name = name.substr(0, name.length() - 4);
			m_scenes.emplace(name, Scene(name));

			c++;
		}
		Lib::app->log("SceneManager", (std::to_string(c) + " scenes loaded.").c_str());
		closedir(dir);
	}
	else {
		Lib::app->error("SceneManager", "couldn't open directory");
	}
}

Scene& SceneManager::getScene(const std::string& name) {
#ifdef _DEBUG
	if (m_scenes.find(name) == m_scenes.end()) {
		Lib::app->error("SceneManager", "couldn't get scene");
	}
#endif
	return m_scenes[name];
}

void SceneManager::changeScene(entityx::EntityManager* entityManager, const std::string& to) {
	if (m_pCurrentScene) {
		m_pCurrentScene->save(entityManager);
	}
	
	// cleaning up the last entites to load the new,
	// entityManager.reset() does hard cleanup of the whole ECS
	for (auto entity : entityManager->entities_with_components<Transform>()) {
		entity.destroy();
	}
	entityManager->softReset();
	
#ifdef _DEBUG
	if (m_scenes.find(to) == m_scenes.end()) {
		Lib::app->error("SceneManager", "couldn't get scene");
	}
#endif
	Lib::app->log("SceneManager", ("changed scene to " + to).c_str());
	m_pCurrentScene = &m_scenes[to];
	m_pCurrentScene->load(entityManager);
}

void SceneManager::createScene(entityx::EntityManager* entityManager, const std::string& name) {
	if (m_scenes.find(name) != m_scenes.end()) {
		Lib::app->error("SceneManager", "scene already exists");
	}

	m_scenes.emplace(name, Scene(name));
	// m_scenes[name].save(entityManager);
}

void SceneManager::saveCurrentScene(entityx::EntityManager* entityManager) {
	if(m_pCurrentScene) {
		m_pCurrentScene->save(entityManager);
	}
}

