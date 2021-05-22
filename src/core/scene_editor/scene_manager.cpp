#include "include/scene_manager.h"

#include <box2d/b2_world.h>

#include "utils/include/dirent.h"
#include "include/lib.h"
#include "../components/2d/include/rigid_body_2d.h"

struct Pig;
struct Bird;

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
	// saving the scene when in editor, otherwise we will have to remake
	// every scene from the start after finishing a level
#if defined(USE_EDITOR)
	if (m_pCurrentScene) {
		m_pCurrentScene->save(entityManager);
	}
#endif
	// cleaning up the last entites to load the new,
	// entityManager.reset() does hard cleanup of the whole ECS
	for (auto entity : entityManager->entities_with_components<Bird>()) {
		auto rb = entity.getComponent<RigidBody2D>()->body;
		rb->GetWorld()->DestroyBody(rb);
		entity.destroy();
	}
	for (auto entity : entityManager->entities_with_components<Pig>()) {
		auto rb = entity.getComponent<RigidBody2D>()->body;
		rb->GetWorld()->DestroyBody(rb);
		entity.destroy();
	}
	entityManager->softReset();
	
#ifdef _DEBUG
	if (m_scenes.find(to) == m_scenes.end()) {
		Lib::app->error("SceneManager", "couldn't get scene");
	}
	Lib::app->log("SceneManager", ("changed scene to " + to).c_str());
#endif
	
	m_pCurrentScene = &m_scenes[to];
	m_pCurrentScene->load(entityManager);
}

void SceneManager::createScene(entityx::EntityManager* entityManager, const std::string& name) {
	if (m_scenes.find(name) != m_scenes.end()) {
		Lib::app->error("SceneManager", "scene already exists");
	}

	m_scenes.emplace(name, Scene(name));
}

void SceneManager::saveCurrentScene(entityx::EntityManager* entityManager) {
	if(m_pCurrentScene) {
		m_pCurrentScene->save(entityManager);
	}
}

