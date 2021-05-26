#include "include/scene_manager.h"

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#include "include/lib.h"
#include "../components/2d/include/rigid_body_2d.h"
#include "../data/include/config_development.h"


struct Transform;
struct Pig;
struct Bird;
struct Obstacle;

SceneManager::SceneManager() : m_pCurrentScene(nullptr) {
	int c = 0;
	for (const auto &entry : fs::recursive_directory_iterator(SCENES_PATH.c_str())) {
        if (entry.path().extension() == ".bin") {
        	std::string name = entry.path().filename().replace_extension("").string();
        	
        	m_scenes.emplace(name, Scene(name));
        	c++;
        }
    }
	Lib::app->log("SceneManager", (std::to_string(c) + " scenes loaded.").c_str());
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
#if !defined(_DEBUG) || defined(USE_EDITOR)
	if (m_pCurrentScene == &m_scenes[to]) return;
#endif
	// for (auto entity : entityManager->entities_with_components<Transform>()) {
	//
	// 	if (auto rb = entity.getComponent<RigidBody2D>()->body) {
	// 		rb->GetWorld()->DestroyBody(rb);
	// 	}
	//
	// 	entity.destroy();
	//
	// }
	// entityManager->softReset();

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
	if (m_pCurrentScene) {
		m_pCurrentScene->save(entityManager);
		Lib::app->log("SceneManager", ("Scene " + m_pCurrentScene->m_fileName + " saved.").c_str());
	}
}
